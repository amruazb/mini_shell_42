/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:42:56 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:05:19 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	int				i;

	i = 0;
	p = b;
	while (len > 0)
	{
		p[i] = c;
		i++;
		len--;
	}
	return (b);
}
