/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_cmd_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:07:50 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 21:26:04 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	last_process_util(t_shell *proc, t_command **av, char **envp)
{
	char	*tmp;

	tmp = get_command(proc, envp, av[(*av)->cmd_len - 1]->cmd);
	if (av[(*av)->cmd_len - 1]->cmd && tmp && av[(*av)->cmd_len - 1]->cmd[0])
	{
		execve(tmp, av[(*av)->cmd_len - 1]->args->array, envp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, (*av)->cmd_len - 1);
}

void	first_process_util(t_shell *proc, t_command **av, char **envp)
{
	char	*tmp;

	if (av[0]->cmd && proc->check > 0)
		check_built_ins_and_exexute(proc, av);
	tmp = get_command(proc, envp, av[0]->cmd);
	if (av[0]->cmd && tmp && av[0]->cmd[0])
	{
		execve(tmp, av[0]->args->array, envp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, 0);
}

int	last_process(t_shell *proc, t_command **av, char **envp)
{
	proc->index = (*av)->cmd_len - 1;
	proc->flag = 0;
	proc->process_id1 = fork();
	if (proc->process_id1 < 0)
		terminate("fork", proc);
	if (proc->process_id1 == 0)
	{
		if (av[(*av)->cmd_len - 1]->total_redirs > 0)
			red_last_proc(av, &proc->flag, proc);
		if (proc->flag == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		if (av[(*av)->cmd_len - 1]->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin(av[(*av)->cmd_len - 1]->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av);
		last_process_util(proc, av, envp);
	}
	return (proc->process_id1);
}

int	first_process(t_shell *proc, t_command **av, char **envp)
{
	proc->index = 0;
	proc->flag = 0;
	proc->process_id = fork();
	if (proc->process_id < 0)
		terminate("fork", proc);
	if (proc->process_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (av[0]->total_redirs > 0)
			red_first_proc(&av[0], &proc->flag, proc);
		if (proc->flag == 0)
			dup2(proc->fd[0][1], STDOUT_FILENO);
		close_pipes(proc);
		if (av[0]->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin(av[0]->cmd);
		first_process_util(proc, av, envp);
	}
	return (proc->process_id);
}

int	pipex_two_cmd(t_command **av, t_shell *proc, char **envp)
{
	signal(SIGINT, SIG_IGN);
	proc->pid1 = first_process(proc, av, envp);
	proc->pid2 = last_process(proc, av, envp);
	close_pipes(proc);
	waitpid(proc->pid2, &proc->error_no, 0);
	waitpid(proc->pid1, 0, 0);
	signal(SIGINT, sig_handler);
	if (WIFEXITED(proc->error_no))
		return (WEXITSTATUS(proc->error_no));
	else if (WIFSIGNALED(proc->error_no))
		return (WTERMSIG(proc->error_no) + 128);
	return (0);
}
