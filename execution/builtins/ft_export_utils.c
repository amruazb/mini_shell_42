/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:59:25 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 15:01:42 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	compare_until_eq(char *str1, char *str2)
{
	int	x;

	x = 0;
	while ((str1[x] && str1[x] != '=') && (str2[x] && str2[x] != '='))
	{
		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
		x++;
	}
	if ((str1[x] == '\0' && str2[x] == '\0') || (str1[x] == '='
			&& str2[x] == '=') || (str1[x] == '=' && str2[x] == '\0')
		|| (str1[x] == '\0' && str2[x] == '='))
		return (0);
	return (1);
}

int	check_and_replace_util(t_exp_var *var, char *replace)
{
	while (var->tmp_list)
	{
		if (compare_until_eq(var->tmp_list->key, replace) == 0)
		{
			if (ft_strchr(replace, '='))
			{
				var->y = 0;
				while (replace[var->y] && replace[var->y] != '=')
					var->y++;
				safe_free(var->tmp_list->key);
				safe_free(var->tmp_list->value);
				var->tmp_list->key = ft_substr(replace, 0, var->y + 1);
				var->tmp_list->value = ft_substr(replace, var->y + 1,
						ft_strlen(replace) - var->y);
			}
			var->flag = 1;
			return (1);
		}
		var->last_index = var->tmp_list->index;
		var->tmp_list = var->tmp_list->next;
	}
	return (0);
}

int	check_and_replace(t_list *head, char *replace)
{
	t_exp_var	var;

	var.tmp_list = head;
	var.flag = 0;
	if (check_and_replace_util(&var, replace) == 1)
		return (0);
	if (var.flag == 0)
	{
		var.y = 0;
		while (replace[var.y] && replace[var.y] != '=')
			var.y++;
		ft_lstadd_back(&head, ft_lstnew(ft_substr(replace, 0, var.y + 1),
				ft_substr(replace, var.y + 1, ft_strlen(replace)),
				var.last_index + 1, var.last_pos + 1));
	}
	return (0);
}

void	print_and_set_flag(t_command **pipe, t_shell *proc)
{
	write(1, "`", 1);
	write(1, (*pipe)->args->array[proc->x],
		ft_strlen((*pipe)->args->array[proc->x]));
	write(1, "'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
	proc->flag = 1;
}

void	ft_env_print_linked(t_shell *proc)
{
	t_list	*tmp;

	tmp = proc->env_list;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '='))
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	garbage_collector(&proc);
	exit(0);
}
