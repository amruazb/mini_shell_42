/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:17:01 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/04/15 13:22:56 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		f((tmp->value));
		tmp = tmp->next;
	}
}

// static void	print(t_list *head);
// void		upper(void *s);
// void	upper(void *s)
// {
// 	int		i;
// 	char	*c;

// 	i = 0;
// 	c = s;
// 	while (c[i])
// 	{
// 		if (c[i] >= 'a' && c[i] <= 'z')
// 			c[i] = c[i] - 32;
// 		i++;
// 	}
// }

// static void	print(t_list *head)
// {
// 	while (head != NULL)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	printf("***********************\n");
// }

// int	main(void)
// {
// 	t_list *nod1;
// 	t_list *nod2;
// 	t_list *nod3;
// 	t_list *lst;
// 	t_list *tmp;
// 	t_list *nod4;
// 	char name1[] = "shamna";
// 	char name2[] = "muhammad";
// 	char name3[] = "fahad";
// 	char name4[] = "Moleri";

// 	nod1 = ft_lstnew(name1);
// 	lst = nod1;
// 	nod2 = ft_lstnew(name2);
// 	nod1->next = nod2;
// 	nod3 = ft_lstnew(name3);
// 	nod2->next = nod3;
// 	nod4 = ft_lstnew(name4);
// 	nod3->next = nod4;
// 	ft_lstiter(lst, upper);
// 	print(lst);
// }