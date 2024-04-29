/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:54:31 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/31 17:37:35 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strdup(const char *s)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (new == NULL)
		return (NULL);
	ft_strcpy(new, (char *)s);
	return (new);
}

// int	main(void)
// {
// 	char *name = "shamna";
// 	printf("%s", ft_strdup(name));
// }