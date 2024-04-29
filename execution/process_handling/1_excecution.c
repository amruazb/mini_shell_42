/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_excecution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:02:54 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 09:53:25 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search(char **envp)
{
	int	x;

	x = -1;
	while (envp[++x])
		if (ft_strnstr(envp[x], "PATH=", 5))
			return (1);
	return (0);
}

void	cmd_not_found(t_command **av, t_shell *proc, int counter)
{
	ft_putstr_fd("sea_shell: ", 2);
	write(2, av[counter]->cmd, ft_strlen(av[counter]->cmd));
	ft_putstr_fd(": command not found\n", 2);
	garbage_collector(&proc);
	exit(127);
}

void	exit_with_code(t_command **av, t_shell *proc)
{
	if (av[proc->index]->cmd[ft_strlen(av[proc->index]->cmd) - 1] == '/')
	{
		ft_putstr_fd(": Is a directory\n", 2);
		garbage_collector(&proc);
		exit(126);
	}
	if (access(av[proc->index]->cmd, F_OK) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		garbage_collector(&proc);
		exit(127);
	}
	else if (access(av[proc->index]->cmd, X_OK) == -1)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		garbage_collector(&proc);
		exit(126);
	}
	else
	{
		ft_putstr_fd(": Is a directory\n", 2);
		garbage_collector(&proc);
		exit(126);
	}
}

void	free_func_one_cmd(t_command **av, t_shell *proc)
{
	if (av[proc->index]->cmd && av[proc->index]->cmd[0] != '\0')
	{
		ft_putstr_fd("sea_shell: ", 2);
		ft_putstr_fd(av[proc->index]->cmd, 2);
		exit_with_code(av, proc);
	}
	garbage_collector(&proc);
	exit(0);
}

void	check_and_execute(t_shell *proc, t_command **av, char **envp, char *tmp)
{
	if ((*av)->cmd && tmp && (*av)->cmd[0])
	{
		execve(tmp, (*av)->args->array, envp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, 0);
}
