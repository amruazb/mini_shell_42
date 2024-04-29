/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:49:22 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:05:23 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dst;
	if (!dst && !src)
		return (NULL);
	if (src == dst)
		return (dst);
	if (dst > src)
	{
		while (len--)
			d[len] = s[len];
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}
