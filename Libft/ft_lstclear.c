/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:17:18 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/04/15 13:21:29 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// static void	del(void *content);

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		next = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = next;
	}
	*lst = NULL;
}

// static void	del(void *content)
// {
// 	content = NULL;
// }

// static void	print(t_list *head)
// {
// 	while (head != NULL)
// 	{
// 		printf("%s\n", head->content);
// 		head = head->next;
// 	}
// 	printf("***********************\n");
// }
// int	main(void)
// {
// 	t_list	*nod1;
// 	t_list	*nod2;
// 	t_list	*nod3;
// 	t_list	**lst;
// 	t_list	*tmp;
// 	t_list	*nod4;

// 	lst = (t_list **)malloc(sizeof(t_list *));
// 	nod1 = ft_lstnew("shamna");
// 	*lst = nod1;
// 	nod2 = ft_lstnew("muhammad");
// 	nod1->next = nod2;
// 	nod3 = ft_lstnew("fahad");
// 	nod2->next = nod3;
// 	nod4 = ft_lstnew("Abootty");
// 	nod3->next = nod4;
// 	print(*lst);
// 	ft_lstclear(&nod3, del);
// 	nod2->next = NULL;
// 	print(*lst);
// }
