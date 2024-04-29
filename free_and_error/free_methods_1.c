/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_methods_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:20:20 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 16:59:04 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_short(char *path, char **path_split)
{
	safe_free(path);
	free_array(path_split);
}

void	free_redirs_list(t_redir **redirlist)
{
	t_redir	*next_node;
	t_redir	*current;

	current = *redirlist;
	if (current)
	{
		while (current)
		{
			next_node = current->next;
			if (current && current->isfreed == false)
			{
				current->isfreed = true;
				free(current->filename);
				free(current);
			}
			current = next_node;
		}
		*redirlist = NULL;
	}
}

static void	free_scommand(t_command ***s_commands)
{
	int	i;

	i = 0;
	if (s_commands && *s_commands)
	{
		while ((*s_commands)[i])
		{
			if ((*s_commands)[i]->isfreed == false)
			{
				(*s_commands)[i]->isfreed = true;
				free((*s_commands)[i]->cmd);
				free_t_char(&(*s_commands)[i]->args);
				free_redirs_list(&(*s_commands)[i]->redirs);
				free((*s_commands)[i]);
			}
			i++;
		}
		free(*s_commands);
		*s_commands = NULL;
	}
}

void	free_compoundlist(t_compound ***nodes)
{
	int	i;

	i = 0;
	if (nodes && *nodes)
	{
		while ((*nodes)[i])
		{
			if ((*nodes)[i]->isfreed == false)
			{
				(*nodes)[i]->isfreed = true;
				if ((*nodes)[i]->s_commands)
					free_scommand(&((*nodes)[i]->s_commands));
				free((*nodes)[i]);
			}
			i++;
		}
	}
	free(*nodes);
	*nodes = NULL;
}
