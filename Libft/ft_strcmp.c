/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:16:39 by aabashee          #+#    #+#             */
/*   Updated: 2024/03/31 11:20:58 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL && s2 == NULL)
	{
		return (0);
	}
	else if (s1 == NULL)
	{
		return (-1);
	}
	else if (s2 == NULL)
	{
		return (1);
	}
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
