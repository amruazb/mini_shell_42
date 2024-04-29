/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:33:13 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:04:00 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;
	size_t	dst_length;
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen(src));
	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	i = dst_length;
	j = 0;
	while (j < src_length && i < (dstsize - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (dstsize != '\0' && i < dstsize)
		dst[i] = '\0';
	if (i < dstsize)
		return (src_length + dst_length);
	else
		return (dstsize + src_length);
}
