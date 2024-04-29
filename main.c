/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:01:56 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 15:49:20 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_code = 0;

bool	should_execute(t_compound *node)
{
	if (node->split_on == AND && g_exit_code != 0)
		return (false);
	else if (node->split_on == OR && g_exit_code == 0)
		return (false);
	else
		return (true);
	return (true);
}

int	process_parens(t_compound **nodes, int start, t_shell *sea_shell)
{
	int	end;

	end = start;
	sea_shell->counter = 0;
	while (nodes[end])
	{
		if (nodes[end]->paren == AFTER_OPEN_PAREN && sea_shell->counter == 0)
			start_execution(nodes[end], sea_shell);
		else if (nodes[end]->paren != AFTER_OPEN_PAREN)
		{
			if (should_execute(nodes[end]))
				start_execution(nodes[end], sea_shell);
			if (nodes[end]->paren == BEFORE_CLOSE_PAREN)
			{
				end++;
				break ;
			}
		}
		else
			end = process_parens(nodes, end, sea_shell);
		end++;
		sea_shell->counter++;
	}
	return (end);
}

void	execute(t_shell *sea_shell)
{
	int	i;

	i = 0;
	while (sea_shell && sea_shell->cmpd_node && sea_shell->cmpd_node[i])
	{
		if (sea_shell->cmpd_node[i]->paren == AFTER_OPEN_PAREN)
		{
			i = process_parens(sea_shell->cmpd_node, i, sea_shell);
			continue ;
		}
		if (i == 0)
			start_execution(sea_shell->cmpd_node[i], sea_shell);
		else if (should_execute(sea_shell->cmpd_node[i]))
			start_execution(sea_shell->cmpd_node[i], sea_shell);
		i++;
	}
}

bool	parse(t_shell *sea_shell)
{
	char	**final_result;
	bool	syntax;

	if (!check_line(sea_shell->line))
		return (g_exit_code = 0, false);
	add_history(sea_shell->line);
	final_result = ft_split_on_delims(sea_shell->line);
	syntax = ft_tokenise(sea_shell, final_result);
	if (syntax == false)
	{
		if (!sea_shell->tokenlist)
			g_exit_code = 0;
		else
			g_exit_code = 258;
		return (false);
	}
	create_compound_array(sea_shell, sea_shell->tokenlist);
	if (!sea_shell->cmpd_node)
		return (free_token_list(&sea_shell->tokenlist), false);
	free_token_list(&sea_shell->tokenlist);
	return (true);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*sea_shell;

	sea_shell = allocateshell();
	signal(SIGQUIT, SIG_IGN);
	checkargs(ac, av);
	checkenv(envp);
	create_envlist(sea_shell, envp);
	while (1)
	{
		init_sea_shell(sea_shell);
		init_signals();
		init_prompt(sea_shell);
		if (parse(sea_shell))
			execute(sea_shell);
		parsing_garbage_collector(&sea_shell);
	}
	free_env_list(&sea_shell->env_list);
	free(sea_shell);
}
