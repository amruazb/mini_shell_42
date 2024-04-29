/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:27:17 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 16:58:53 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_char(t_char **char_struct)
{
	int	i;

	i = -1;
	if (*char_struct)
	{
		if ((*char_struct)->array)
		{
			if ((*char_struct)->isfreed == false)
			{
				(*char_struct)->isfreed = true;
				while ((*char_struct)->array[++i])
					free((*char_struct)->array[i]);
			}
			free((*char_struct)->array);
			(*char_struct)->array = NULL;
		}
		free(*char_struct);
		*char_struct = NULL;
	}
}

void	free_token_list(t_token **tokenlist)
{
	t_token	*next_node;
	t_token	*current;

	current = *tokenlist;
	if (current)
	{
		while (current)
		{
			next_node = current->next;
			if (current && current->isfreed == false)
			{
				current->isfreed = true;
				free(current->value);
				free(current);
			}
			current = next_node;
		}
		*tokenlist = NULL;
	}
}

void	free_env_list(t_list **head)
{
	t_list	*next;
	t_list	*current;

	current = *head;
	if (current)
	{
		while (current)
		{
			next = current->next;
			if (current && current->isfreed == false)
			{
				current->isfreed = true;
				free(current->key);
				free(current->value);
				free(current);
			}
			current = next;
		}
		*head = NULL;
	}
}

void	garbage_collector(t_shell **sea_shell)
{
	if (sea_shell && *sea_shell)
	{
		if ((*sea_shell)->isfreed == false)
		{
			(*sea_shell)->isfreed = true;
			if ((*sea_shell)->env_vars)
				free_t_char(&((*sea_shell)->env_vars));
			if ((*sea_shell)->env_list)
				free_env_list(&(*sea_shell)->env_list);
			if ((*sea_shell)->line)
				safe_free((*sea_shell)->line);
			if ((*sea_shell)->cmpd_node)
				free_compoundlist(&((*sea_shell)->cmpd_node));
			if ((*sea_shell)->tokenlist)
				free_token_list(&((*sea_shell)->tokenlist));
			if ((*sea_shell)->result)
				safe_free((*sea_shell)->result);
		}
		free(*sea_shell);
	}
}

void	parsing_garbage_collector(t_shell **sea_shell)
{
	if (sea_shell && *sea_shell)
	{
		if ((*sea_shell)->isfreed == false)
		{
			(*sea_shell)->isfreed = true;
			if ((*sea_shell)->env_vars)
				free_t_char(&((*sea_shell)->env_vars));
			if ((*sea_shell)->line)
				safe_free((*sea_shell)->line);
			if ((*sea_shell)->tokenlist)
				free_token_list(&((*sea_shell)->tokenlist));
			if ((*sea_shell)->cmpd_node)
				free_compoundlist(&((*sea_shell)->cmpd_node));
		}
	}
}
