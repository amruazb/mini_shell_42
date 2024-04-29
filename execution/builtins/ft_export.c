/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:00:47 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 15:01:30 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_validate_export(char *str)
{
	int	x;

	x = 0;
	if (ft_isalpha(str[0]) == 1 || str[0] == '_')
	{
		while (str[x] && str[x] != '=')
		{
			if (str[x] == '_' || ft_isalnum(str[x]) == 1)
				x++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	ft_export_to_linked(t_command **pipe, t_shell *prc)
{
	prc->x = 0;
	while ((*pipe)->args->array[++prc->x])
	{
		if (ft_validate_export((*pipe)->args->array[prc->x]) == 1)
			print_and_set_flag(pipe, prc);
		else
			check_and_replace(prc->env_list, (*pipe)->args->array[prc->x]);
	}
	return (prc->flag);
}

int	ft_export_print_linked(t_command **pipe, t_shell *prc)
{
	int	x;

	sort_list(prc->env_list);
	re_index(prc->env_list);
	prc->flag = 0;
	prc->temp_list = prc->env_list;
	x = 0;
	if ((*pipe)->args->array[1])
		x = ft_export_to_linked(pipe, prc);
	else
	{
		prc->temp_list = prc->env_list;
		while (prc->temp_list)
		{
			if (ft_strchr(prc->temp_list->key, '='))
				printf("declare -x %s\"%s\"\n", prc->temp_list->key,
					prc->temp_list->value);
			else
				printf("declare -x %s\n", prc->temp_list->key);
			prc->temp_list = prc->temp_list->next;
		}
	}
	if ((*pipe)->cmd_len > 1)
		garbage_collector(&prc);
	return (x);
}

int	ft_unset_check_and_unset(t_list **main_head, char **args)
{
	t_exp_var	var;

	var.x = -1;
	var.tmp_ex = NULL;
	while (args[++var.x])
	{
		if (ft_strchr(args[var.x], '='))
			return (write(2, args[var.x], ft_strlen(args[var.x])),
				ft_putstr_fd(" : not a valid identifier\n", 2), 1);
		var.tmp_list = *main_head;
		while (var.tmp_list)
		{
			if (ft_strchr(var.tmp_list->key, '='))
				var.tmp_ex = ft_strjoin(args[var.x], "=");
			else
				var.tmp_ex = ft_strdup(args[var.x]);
			if (ft_strcmp(var.tmp_list->key, var.tmp_ex) == 0)
				return (safe_free(var.tmp_ex), remove_element(main_head,
						var.tmp_list->index));
			safe_free(var.tmp_ex);
			var.tmp_list = var.tmp_list->next;
		}
	}
	return (0);
}

int	ft_unset(t_command **pipe, t_shell *proc)
{
	int	x;
	int	res;

	x = 0;
	res = 0;
	if ((*pipe)->args->array[1])
		while ((*pipe)->args->array[++x])
			res = ft_unset_check_and_unset(&proc->env_list,
					&(*pipe)->args->array[x]);
	if ((*pipe)->cmd_len > 1)
		garbage_collector(&proc);
	return (res);
}
