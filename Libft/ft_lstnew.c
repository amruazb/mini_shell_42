/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 05:56:35 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/04/15 12:07:47 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(char *key, char *value, int index, int position)
{
	t_list	*node;

	(void)position;
	node = (t_list *)malloc(sizeof(t_list));
	if (node)
	{
		node->key = ft_strdup(key);
		node->value = ft_strdup(value);
		node->index = index;
		node->isfreed = false;
		node->next = NULL;
	}
	free(key);
	free(value);
	return (node);
}
