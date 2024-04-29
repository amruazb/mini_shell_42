/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:03:43 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:09:00 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	end = ft_strlen(s1);
	if (start == end)
		return (ft_strdup(s1));
	while (s1[start] != '\0' && ft_strchr(set, (int)s1[start]))
		start++;
	while (end > start && ft_strchr(set, (int)s1[end]))
		end--;
	end++;
	return (ft_substr(s1, start, end - start));
}

// int	main(void)
// {
// 	char	*s1;
// 	char	*set;

// 	s1 = " ****shamna****";
// 	set = "     *";
// 	printf("%s", ft_strtrim(s1, set));
// }
