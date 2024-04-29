/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:21:52 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:05:45 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int	main(void)
// {
// 	t_list *nod1;
// 	t_list *nod2;
// 	t_list *nod3;

// 	nod1 = ft_lstnew("shamna");
// 	nod2 = ft_lstnew("muhammad");
// 	nod1->next = nod2;
// 	nod3 = ft_lstnew("Mrs.");
// 	nod2->next = nod3;
// 	printf("%d", ft_lstsize(nod1));
// }