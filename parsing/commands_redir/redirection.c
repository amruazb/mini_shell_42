/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:49:41 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 13:55:03 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redir	*get_to_last(t_redir *lst)
{
	t_redir	*to_last;

	to_last = lst;
	while (to_last != NULL && to_last->next != NULL)
		to_last = to_last->next;
	return (to_last);
}
/*
** Function: static int count_redirs(t_redir *redirs)
** Description: Counts the number 
** of redirections in a linked list of redirection nodes.
*/

int	count_redirs(t_redir *redirs)
{
	t_redir	*temp;
	int		total;

	total = 0;
	temp = redirs;
	while (temp)
	{
		total++;
		temp = temp->next;
	}
	return (total);
}

/*
** Function: static void
** add_to_redir_list(t_redir **redirList, t_redir *redirNode)
** Description: Adds a redirection node to the end of a redirection list.
*/

static void	add_to_redir_list(t_redir **redirList, t_redir *redirNode)
{
	t_redir	*to_last;

	if (*redirList == NULL)
		*redirList = redirNode;
	else
	{
		to_last = get_to_last(*redirList);
		to_last->next = redirNode;
	}
}

/*
** Function: static t_redir_type assign_redir_type(char *arg)
** Description: Assigns the type of redirection based on the argument.
*/
static t_redir_type	assign_redir_type(char *arg)
{
	t_redir_type	type;

	if (ft_strcmp(arg, "<") == 0)
		type = INPUT;
	else if (ft_strcmp(arg, ">") == 0)
		type = OUTPUT;
	else if (ft_strcmp(arg, ">>") == 0)
		type = APPEND;
	else
		type = HEREDOC;
	return (type);
}

/*
** Function: void
** fill_redirs(t_command *scommand, t_token *redir, t_token *filename)
** Description: Fills a subcommand node with redirection information.
*/
void	fill_redirs(t_command *scommand, t_token *redir, t_token *filename)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	new_redir->type = assign_redir_type(redir->value);
	new_redir->filename = ft_strdup(filename->value);
	new_redir->isfreed = false;
	new_redir->next = NULL;
	if (new_redir->type == INPUT || new_redir->type == HEREDOC)
		add_to_redir_list(&scommand->redirs, new_redir);
	if (new_redir->type == OUTPUT || new_redir->type == APPEND)
		add_to_redir_list(&scommand->redirs, new_redir);
}
