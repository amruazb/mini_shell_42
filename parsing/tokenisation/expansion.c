/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:08:17 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 22:25:18 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// Function to create a new token node
static t_token	*expand_new_token_node(char *arg)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node)
	{
		node->value = ft_strdup(arg);
		node->type = WORD;
		node->isfreed = false;
		node->next = NULL;
	}
	return (node);
}
/* 
**Function to get the last token node in a token list 
*/

static t_token	*get_to_last(t_token *lst)
{
	t_token	*to_last;

	to_last = lst;
	while (to_last != NULL && to_last->next != NULL)
		to_last = to_last->next;
	return (to_last);
}
/* 
**function to add a token node to the end of a token list
*/

void	add_token_node(t_token **tokenlist, t_token *tokenNode)
{
	t_token	*to_last;

	if (*tokenlist)
	{
		to_last = get_to_last(*tokenlist);
		to_last->next = tokenNode;
		tokenNode->next = NULL;
	}
	else
	{
		*tokenlist = tokenNode;
	}
}

/*
** Takes a double pointer to a token list,
** a string str, and a t_shell struct as arguments
** Expands the string and creates a new token node
** for each non-empty string in the expanded string
** Adds each new token node to the token list
*/

void	expand_token(t_token **tokenlist, char *str, t_shell *seashell)
{
	char	**temp;
	int		index;
	char	*expanded_str;

	expanded_str = ft_strdup(str);
	expanded_str = final_expanded_str(seashell, expanded_str);
	temp = ft_space(expanded_str);
	index = -1;
	while (temp[++index])
	{
		if (ft_strcmp("", temp[index]) == 0)
			continue ;
		add_token_node(tokenlist, expand_new_token_node(temp[index]));
	}
	free_array(temp);
	safe_free(expanded_str);
}
/*
** @brief Function to create the final expanded string
** Takes a t_shell struct and a string str as arguments
** Continues expanding the string until no more expansions are needed
 */

char	*final_expanded_str(t_shell *seashell, char *str)
{
	char	*final_str;
	char	*expand_temp;

	final_str = ft_strdup(str);
	while (needs_expansion(final_str) == true)
	{
		expand_temp = new_expanded_str(seashell, final_str);
		safe_free(final_str);
		final_str = ft_strdup(expand_temp);
		safe_free(expand_temp);
	}
	safe_free(str);
	return (final_str);
}
