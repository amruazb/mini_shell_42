/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:56:11 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:10:25 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// char	upper(unsigned int i, char c)
// {
// 	if (c >= 'a' && c <= 'z')
// 		c -= 32;
// 	return (c);
// }
// int	main(void)
// {
// 	char str[] = "SHamna abootty";
// 	char *str2;
// 	str2 = ft_strmapi(str, *upper);
// 	printf("%s", str2);
// }