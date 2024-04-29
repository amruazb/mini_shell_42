/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:06:05 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 22:06:12 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token_node(char *arg)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node)
	{
		node->value = ft_strdup(arg);
		node->type = assign_t_token_type(arg);
		node->isfreed = false;
		node->next = NULL;
	}
	return (node);
}

t_token	*create_token_list(char **tokens, t_shell *seashell)
{
	t_token	*tokenlist;
	int		i;

	tokenlist = NULL;
	i = -1;
	seashell->is_heredoc = false;
	while (tokens[++i])
	{
		if (needs_expansion(tokens[i]) == true && seashell->is_heredoc == false)
		{
			expand_token(&tokenlist, tokens[i], seashell);
			continue ;
		}
		seashell->is_heredoc = false;
		if (tokens[i] && array_strchr(tokens[i], '*'))
		{
			if (filename_expansion(&tokenlist, tokens[i]))
				continue ;
		}
		if (tokens[i] && ft_strcmp("", tokens[i]) != 0)
			add_token_node(&tokenlist, new_token_node(tokens[i]));
		if (ft_strcmp("<<", tokens[i]) == 0)
			seashell->is_heredoc = true;
	}
	return (tokenlist);
}

bool	ft_tokenise(t_shell *sea_shell, char **str_tokens)
{
	if (!str_tokens)
		return (false);
	sea_shell->tokenlist = create_token_list(str_tokens, sea_shell);
	free_array(str_tokens);
	if (sea_shell->tokenlist == NULL)
		return (sea_shell->tokenlist);
	if (token_syntax_check(sea_shell->tokenlist) == false)
	{
		g_exit_code = 127;
		return (false);
	}
	token_quote_removal(sea_shell->tokenlist);
	return (true);
}
