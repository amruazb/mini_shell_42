/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 06:24:25 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:07:08 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	unsigned int	i;
	unsigned int	x;

	i = 0;
	x = 0;
	if (str == 0 && n == 0)
		return (NULL);
	if (to_find[x] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < n)
	{
		while ((str[i + x] == to_find[x]) && (str[i + x] != '\0') && (i
				+ x) < n)
			x++;
		if (to_find[x] == '\0')
			return ((char *)str + i);
		x = 0;
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char *str;
// 	char *search;
// 	str = NULL;
// 	search = "fake";
// 	printf("%s", ft_strnstr(str, search, 4));
// }