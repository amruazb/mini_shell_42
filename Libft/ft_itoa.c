/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:25:22 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:09:42 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_len(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		i++;
		num = num / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*s;
	size_t			len;
	unsigned int	num;

	len = ft_len(n);
	num = n;
	if (n < 0)
	{
		num = -1 * n;
		len++;
	}
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	s[len] = '\0';
	if (num == 0)
		s[--len] = 0 + '0';
	while (num)
	{
		s[--len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}

// int	main(void)
// {
// 	int a = 1234;
// 	char *s = ft_itoa(a);
// 	printf("%s", s);
// }