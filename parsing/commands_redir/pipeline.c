/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:36:33 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 13:48:09 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Function: static void 
	add_token_to_args(t_command *scommand, t_token *current_token)
** Description: Adds a token's value to the arguments of a subcommand node.
*/
static void	add_token_to_args(t_command *scommand, t_token *current_token)
{
	char	**temp_array;

	if (scommand->args == NULL)
	{
		scommand->args = (t_char *)malloc(sizeof(t_char));
		scommand->args->array = (char **)malloc(sizeof(char *) * 2);
		scommand->args->array[0] = ft_strdup(current_token->value);
		scommand->args->array[1] = NULL;
		scommand->args->isfreed = false;
	}
	else
	{
		temp_array = (char **)malloc(sizeof(char *) * 2);
		temp_array[0] = ft_strdup(current_token->value);
		temp_array[1] = NULL;
		scommand->args->array = append_array(scommand->args->array, temp_array);
		free_array(temp_array);
	}
}

/*
** Function: void fill_scmnd(t_command *scommand, t_token *start, t_token *end)
** Description: Fills a subcommand node with information from token list.
*/

void	fill_scmnd(t_command *scommand, t_token *start, t_token *end)
{
	t_token	*current_token;

	current_token = start;
	while (current_token && current_token != end->next)
	{
		if (current_token->type == REDIR)
		{
			fill_redirs(scommand, current_token, current_token->next);
			current_token = current_token->next->next;
		}
		while (current_token
			&& (current_token != end->next && current_token->type != REDIR))
		{
			if (ft_strcmp(")", current_token->value) != 0)
				add_token_to_args(scommand, current_token);
			current_token = current_token->next;
		}
	}
}

/*
** Function: int count_pipes(t_token *start, t_token *end)
** Description: Counts the number of pipes between two tokens.
*/
int	count_pipes(t_token *start, t_token *end)
{
	int		i;
	t_token	*temp;

	temp = start;
	i = 1;
	while (temp && temp->value != NULL && temp != end->next)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}
/*
** Function: t_command *create_scmnd_node(t_token *start, t_token *end)
** Description: Creates a subcommand node with information from token list.
*/

t_command	*create_scmnd_node(t_token *start, t_token *end)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->redirs = NULL;
	command->args = NULL;
	command->isfreed = false;
	fill_scmnd(command, start, end);
	if (command->args && command->args->array[0])
	{
		command->cmd = ft_strdup(command->args->array[0]);
		command->args_len = ft_array_len(command->args->array);
	}
	command->total_redirs = count_redirs(command->redirs);
	return (command);
}

/*
*`* Function: void create_compound_node
*(t_token *start, t_token *end, t_shell *sea_shell, t_compound *node)
** Description: Creates a compound node with subcommands.
*/
void	create_compound_node(t_token *start,
	t_token *end, t_shell *sea_shell, t_compound *node)
{
	t_token	*temp;
	t_token	*temp_end;
	int		i;

	node->s_commands = (t_command **)malloc(sizeof(t_command *)
			* (count_pipes(start, end) + 1));
	if (!node->s_commands)
		free_and_exit(sea_shell, "memory allocation failure");
	temp = start;
	i = -1;
	while (++i < count_pipes(start, end))
	{
		temp_end = temp;
		while (temp_end->next != NULL && temp_end->next
			!= end->next && temp_end->next->type != PIPE)
			temp_end = temp_end->next;
		node->s_commands[i] = create_scmnd_node(temp, temp_end);
		node->s_commands[i]->cmd_len = count_pipes(start, end);
		if (temp_end->next != NULL && temp_end->next != end->next)
			temp = temp_end->next->next;
		else
			temp = NULL;
	}
	node->s_commands[i] = NULL;
}
