/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:11:32 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:04:04 by shmuhamm         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	size_new;

	if (!s1)
		return (NULL);
	size_new = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (size_new + 1));
	if (new == NULL)
		return (0);
	ft_strcpy(new, (char *)s1);
	ft_strlcat(new, s2, size_new + 1);
	return (new);
}

// int	main(void)
// {
// 	char	*f_name;
// 	char	*s_name;

// 	f_name = "shamna";
// 	s_name = "Abootty";
// 	printf("%s", ft_strjoin(f_name, s_name));
// }
