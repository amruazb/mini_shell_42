/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:03:12 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:04:31 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	*ft_undomem(char **s, int i)
{
	while (--i <= 0)
	{
		free(s[i]);
	}
	free(s);
	return (NULL);
}

static char	*ft_wcpy(char const *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s, i);
	str[i] = '\0';
	return (str);
}

static int	ft_wc(char const *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i])
			wc++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wc);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		w_count;
	char	**split_array;

	if (!s)
		return (NULL);
	w_count = ft_wc(s, c);
	split_array = (char **)malloc(sizeof(char *) * (w_count + 1));
	i = 0;
	if (!split_array)
		return (0);
	while (i < w_count)
	{
		while (s && *s == c)
			s++;
		split_array[i] = ft_wcpy(s, c);
		if (!split_array)
			ft_undomem(split_array, i);
		s += ft_strlen(split_array[i]);
		i++;
	}
	split_array[i] = 0;
	return (split_array);
}

// int	main(void)
// {
// 	char names[] = "hello!";
// 	int i;
// 	i = 0;
// 	char **split = ft_split(names, ' ');
// 	// 	while (split[i])
// 	// 	{
// 	// 		printf("%s\n", split[i]);
// 	// 		i++;
// 	// 	}
// }