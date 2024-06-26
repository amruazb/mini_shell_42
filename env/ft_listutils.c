/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:41:13 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 17:41:37 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * sort_list: is a function that sort linked list
 * @head: the head of linked lists
 */

void	sort_list(t_list *head)
{
	t_list	*current;
	t_list	*compare;
	char	*temp_content;
	char	*temp_value;

	current = head;
	while (current && current->next != NULL)
	{
		compare = current->next;
		while (compare != NULL)
		{
			if (ft_strcmp(current->key, compare->key) > 0)
			{
				temp_content = current->key;
				temp_value = current->value;
				current->key = compare->key;
				current->value = compare->value;
				compare->key = temp_content;
				compare->value = temp_value;
			}
			compare = compare->next;
		}
		current = current->next;
	}
}

/**
 * re_index: is a function that gives the index for the linked list
 * @head: pointer pointing to head of the linked list
 */
void	re_index(t_list *head)
{
	t_list	*prev;
	int		x;

	x = 0;
	prev = head;
	while (prev)
	{
		prev->index = x++;
		prev = prev->next;
	}
}

t_char	*linked_to_array(t_list *head)
{
	t_list	*tmp;
	t_char	*env_vars;
	int		len;
	int		x;

	len = ft_lstsize(head);
	if (len == 0)
		return (NULL);
	tmp = head;
	env_vars = (t_char *)malloc(sizeof(t_char));
	env_vars->array = (char **)malloc(sizeof(char *) * (len + 1));
	env_vars->isfreed = false;
	x = 0;
	while (tmp)
	{
		env_vars->array[x] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
		x++;
	}
	env_vars->array[x] = NULL;
	x = 0;
	return (env_vars);
}

static void	first_element(t_list **head)
{
	t_list	*current;

	current = *head;
	*head = current->next;
	safe_free(current->key);
	safe_free(current->value);
	safe_free(current);
}

int	remove_element(t_list **head, int index)
{
	t_list	*current;
	t_list	*prev;

	current = *head;
	prev = NULL;
	if (index == 0)
		first_element(head);
	else
	{
		while (current != NULL)
		{
			if (current->index == index)
			{
				prev->next = current->next;
				safe_free(current->key);
				safe_free(current->value);
				safe_free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
	return (re_index(*head), 0);
}
