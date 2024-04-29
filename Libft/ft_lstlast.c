/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:41:14 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/03/26 15:05:58 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp == 0)
		return (lst);
	while (tmp->next != 0)
		tmp = tmp->next;
	return (tmp);
}

// int	main(void)
// {
// 	t_list *nod1;
// 	t_list *nod2;
// 	t_list *nod3;
// 	t_list *nod;

// 	nod1 = ft_lstnew("shamna");
// 	nod2 = ft_lstnew("muhammad");
// 	nod1->next = nod2;
// 	nod3 = ft_lstnew("Mrs.");
// 	nod2->next = nod3;
// 	nod = ft_lstlast(nod1);
// 	printf("%s", nod->content);
// }