/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:19:56 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 13:25:36 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Function: static int count_compound(t_token *headtoken)
** Description: Counts the number of compound 
**commands in a linked list of tokens.
*/
static int	count_compound(t_token *headtoken)
{
	int		i;
	t_token	*temp;

	temp = headtoken;
	i = 1;
	while (temp)
	{
		if (temp->type == AND || temp->type == OR)
			i++;
		temp = temp->next;
	}
	return (i);
}

/*
** Function: t_token_type 
**fill_compound_node(t_shell *sea_shell, t_token *temp, t_token *end)
** Description: Fills a compound node with relevant information.
*/

t_token_type	
	fill_compound_node(t_shell *sea_shell, t_token *temp, t_token *end)
{
	sea_shell->cmpd_node[sea_shell->i]
		= (t_compound *)malloc(sizeof(t_compound));
	if (!sea_shell->cmpd_node[sea_shell->i])
		free_and_exit(sea_shell, "memory allocation failure");
	create_compound_node(temp, end, sea_shell,
		sea_shell->cmpd_node[sea_shell->i]);
	sea_shell->cmpd_node[sea_shell->i]->cmd_len = count_pipes(temp, end);
	sea_shell->cmd_len = sea_shell->cmpd_node[sea_shell->i]->cmd_len;
	sea_shell->cmpd_node[sea_shell->i]->split_on = sea_shell->split_on;
	sea_shell->cmpd_node[sea_shell->i]->paren = sea_shell->paren;
	sea_shell->cmpd_node[sea_shell->i]->isfreed = false;
	if (end && end->next && end->next->type == OR)
		return (OR);
	if (end && end->next && end->next->type == AND)
		return (AND);
	return (PIPE);
}

/*
** Function: void check_paren_type(t_shell *sea_shell, t_token *end)
** Description: Checks the type of closing parenthesis.
*/
void	check_paren_type(t_shell *sea_shell, t_token *end)
{
	if (end->next->type == CLOSE_PAREN)
		sea_shell->paren = BEFORE_CLOSE_PAREN;
}

/*
** Function: void go_past_open_paren(t_token **temp, t_shell *sea_shell)
** Description: Moves past open parenthesis tokens.
*/

void	go_past_open_paren(t_token **temp, t_shell *sea_shell)
{
	while (*temp && (*temp)->type == OPEN_PAREN)
	{
		*temp = (*temp)->next;
		sea_shell->paren = AFTER_OPEN_PAREN;
	}
}

void	create_compound_array(t_shell *sea_shell, t_token *headtoken)
{
	t_token	*temp;
	t_token	*end;

	temp = headtoken;
	sea_shell->cmpd_node = (t_compound **)malloc(sizeof(t_compound *)
			* (count_compound(headtoken) + 1));
	sea_shell->i = -1;
	while (++sea_shell->i < count_compound(headtoken))
	{
		sea_shell->paren = NOT_PAREN;
		go_past_open_paren(&temp, sea_shell);
		end = temp;
		while (end->next != NULL
			&& end->next->type != OR && end->next->type != AND)
		{
			check_paren_type(sea_shell, end);
			end = end->next;
		}
		sea_shell->split_on = fill_compound_node(sea_shell, temp, end);
		if (end && end->next != NULL)
			end = end->next->next;
		temp = end;
	}
	sea_shell->cmpd_node[sea_shell->i] = NULL;
}
