/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:30:26 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 16:43:32 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	array_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (true);
		i++;
	}
	if ((char)c == '\0')
		return (true);
	return (false);
}

static char	**ft_joinarray(char **final, char **s1, char **s2)
{
	int	i;
	int	j;
	int	total_rows;

	if (!final || !s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < ft_token_count(s1))
	{
		final[++j] = ft_strdup((char *)s1[i]);
	}
	i = -1;
	while (++i < ft_token_count(s2))
		final[++j] = ft_strdup((char *)s2[i]);
	total_rows = ft_token_count(s1) + ft_token_count(s2);
	final[total_rows] = NULL;
	return (final);
}

char	**append_array(char **s1, char **s2)
{
	int		s1_rows;
	int		s2_rows;
	char	**final;

	s1_rows = 0;
	s2_rows = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_rows = ft_token_count(s1);
	s2_rows = ft_token_count(s2);
	final = (char **)malloc((s1_rows + s2_rows + 1) * sizeof(char *));
	if (final == NULL)
		return (final);
	final = ft_joinarray(final, s1, s2);
	free_array(s1);
	return (final);
}

int	ft_array_len(char **str)
{
	int	str_rows;

	str_rows = 0;
	if (!str)
		return (0);
	while (str[str_rows] != NULL)
		str_rows++;
	return (str_rows);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			free(array[i++]);
		free(array);
	}
}
