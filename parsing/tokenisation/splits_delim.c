/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_delim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:55:01 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 15:59:05 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_end_index(char *s, char *metachars, int start)
{
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	if (s[start] && array_strchr(metachars, s[start]))
	{
		if (s[start + 1] && s[start] == s[start + 1] && !array_strchr("()",
				s[start]))
			return (start += 2);
		else
			return (start + 1);
	}
	else
	{
		while (s[start])
		{
			set_quote_flag(&quotes, s[start]);
			if (array_strchr(metachars, s[start]) && !quotes.single_q
				&& !quotes.double_q)
				break ;
			start++;
		}
	}
	return (start);
}

static int	total_tokens(char *s, char *metachars)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!array_strchr(metachars, s[i]))
			i = get_end_index(s, metachars, i);
		else
		{
			if (s[i + 1] && (s[i] == s[i + 1]) && !array_strchr("()", s[i]))
				i += 2;
			else
				i++;
		}
		count++;
	}
	return (count);
}

static char	**split_on_meta(char *s, char **array, char *metachars)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < (total_tokens(s, metachars)))
	{
		if (s[start] && array_strchr(metachars, s[start]))
		{
			if (s[start + 1] && s[start] == s[start + 1] && !array_strchr("()",
					s[start]))
				array[i++] = ft_substr(s, start, 2);
			else
				array[i++] = ft_substr(s, start, 1);
		}
		else
			array[i++] = ft_substr(s, start, get_end_index(s, metachars, start)
					- start);
		start = get_end_index(s, metachars, start);
	}
	array[i] = NULL;
	return (array);
}

static char	**ft_strtok(char *s)
{
	char	**array;
	char	*metachars;

	metachars = "&<|>()";
	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (total_tokens(s, metachars) + 1));
	if (array == NULL)
		return (NULL);
	array = split_on_meta(s, array, metachars);
	return (array);
}

char	**ft_split_on_delims(char *str)
{
	char	**temp_tokens;
	char	**final_tokens;
	char	**next_tokens;
	int		i;

	i = -1;
	temp_tokens = ft_space(str);
	if (temp_tokens == NULL)
		return (NULL);
	while (temp_tokens[++i] != NULL)
	{
		if (i == 0)
			final_tokens = ft_strtok(temp_tokens[i]);
		else
		{
			next_tokens = ft_strtok(temp_tokens[i]);
			final_tokens = append_array(final_tokens, next_tokens);
			free_array(next_tokens);
		}
	}
	return (free_array(temp_tokens), final_tokens);
}
