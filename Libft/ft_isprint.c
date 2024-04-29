/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:19:41 by shmuhamm          #+#    #+#             */
/*   Updated: 2023/07/13 18:15:51 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int a;

// 	a = '\n';
// 	printf("%d", ft_isprint(a));
// 	printf("\n%d", isprint(a));
// }