/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:47:16 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 17:04:43 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_end_index_sp(char *s, char *white_spaces, int start)
{
	t_quote	quotes;
	int		end;

	quotes.single_q = false;
	quotes.double_q = false;
	end = start;
	while (s[end])
	{
		set_quote_flag(&quotes, s[end]);
		if (array_strchr(white_spaces, s[end]) && !quotes.single_q
			&& !quotes.double_q)
			break ;
		end++;
	}
	return (end);
}

static int	num_words(char *s, char *white_spaces)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!array_strchr(white_spaces, s[i]))
		{
			i = get_end_index_sp(s, white_spaces, i);
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	**remove_spaces(char *s, char **array, char *white_spaces)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < (num_words(s, white_spaces)))
	{
		while (s[start] && (array_strchr(white_spaces, s[start])))
			start++;
		array[i++] = ft_substr(s, start,
				(get_end_index_sp(s, white_spaces, start)
					- start));
		start = get_end_index_sp(s, white_spaces, start);
	}
	array[i] = NULL;
	return (array);
}

char	**ft_space(char *s)
{
	char	**array;
	char	*white_spaces;

	white_spaces = "\t  \n\v\f\b";
	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (num_words(s, white_spaces) + 1));
	if (array == NULL)
		return (NULL);
	array = remove_spaces(s, array, white_spaces);
	return (array);
}
