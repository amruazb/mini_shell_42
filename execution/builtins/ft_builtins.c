/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:13:26 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 10:59:53 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_nns(char *str)
{
	int	x;

	x = 0;
	if (!str)
		return (1);
	if (str[x] != '-' || str[x + 1] != 'n')
		return (1);
	while (str[++x])
		if (str[x] != 'n')
			return (1);
	return (0);
}

void	ft_print_echo(t_command **pipe, int x)
{
	int	flag;

	flag = 0;
	while (++x < (*pipe)->args_len)
	{
		if ((check_nns((*pipe)->args->array[x]) == 0 && flag == 0)
			|| !(*pipe)->args->array[x])
			continue ;
		if ((*pipe)->args->array[x + 1] == NULL)
			printf("%s", (*pipe)->args->array[x]);
		else
			printf("%s ", (*pipe)->args->array[x]);
		flag = 1;
	}
}

void	ft_echo(t_command **pipe, t_shell *proc)
{
	if (pipe[proc->index]->args_len == 1)
	{
		printf("\n");
		garbage_collector(&proc);
	}
	else if (check_nns(pipe[proc->index]->args->array[1]) == 0)
	{
		ft_print_echo(&pipe[proc->index], 1);
		garbage_collector(&proc);
	}
	else
	{
		ft_print_echo(&pipe[proc->index], 0);
		printf("\n");
		garbage_collector(&proc);
	}
	exit(0);
}

void	ft_pwd(t_shell *data)
{
	char	res[4096];
	char	*pwd;

	pwd = getcwd(res, 4096);
	if (!pwd)
	{
		ft_putstr_fd("Error: sorry dir is deleted or incorrect!\n", 2);
		garbage_collector(&data);
		exit(1);
	}
	printf("%s\n", pwd);
	garbage_collector(&data);
	exit(0);
}

void	ft_exit(t_command **pipe, t_shell *proc)
{
	int		number;
	int		i;
	char	*arg;

	arg = pipe[proc->index]->args->array[1];
	if (pipe[proc->index]->args->array[1] == NULL)
	{
		garbage_collector(&proc);
		exit(g_exit_code);
	}
	else
	{
		i = 0;
		while (arg[i] != '\0')
		{
			if (arg[i] < '0' || arg[i] > '9')
				ft_writing(pipe, proc);
			i++;
		}
		number = ft_small_atoi(arg);
		garbage_collector(&proc);
		exit(number);
	}
}
