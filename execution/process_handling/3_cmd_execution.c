/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cmd_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:10:28 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 12:10:58 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes(t_shell *proc)
{
	int	x;

	x = -1;
	while (++x < proc->total_pipes)
	{
		close(proc->fd[x][0]);
		close(proc->fd[x][1]);
	}
}

void	terminate(char *display, t_shell *sea_shell)
{
	if (access(display, W_OK) == -1 || access(display, R_OK) == -1)
		perror(display);
	else
		perror(display);
	close_pipes(sea_shell);
	garbage_collector(&sea_shell);
	exit(1);
}

void	middle_proc_execute(t_shell *proc, t_command **av, char **envp,
		int counter)
{
	char	*tmp;

	tmp = get_command(proc, envp, av[counter]->cmd);
	if (av[counter]->cmd && tmp && av[counter]->cmd[0])
	{
		proc->index = counter;
		execve(tmp, av[counter]->args->array, envp);
		safe_free(tmp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, counter);
}

void	middl_process(t_shell *proc, t_command **av, char **envp, int counter)
{
	proc->index = counter;
	proc->flag_out = 0;
	proc->flag_in = 0;
	proc->process_id = fork();
	if (proc->process_id < 0)
		terminate("fork", proc);
	if (proc->process_id == 0)
	{
		if (av[counter]->total_redirs > 0)
			red_middle(av, &proc->flag_out, &proc->flag_in, proc);
		if (proc->flag_out == 0)
			dup2(proc->fd[proc->counter + 1][1], STDOUT_FILENO);
		if (proc->flag_in == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		if (av[counter]->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin(av[counter]->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av);
		middle_proc_execute(proc, av, envp, counter);
	}
}

int	pipex_three_cmd(t_command **av, t_shell *proc, char **envp)
{
	proc->x = 0;
	proc->counter = 0;
	signal(SIGINT, SIG_IGN);
	first_process(proc, av, envp);
	while (proc->counter < proc->middle_scommand)
	{
		middl_process(proc, av, envp, proc->counter + 1);
		proc->counter++;
	}
	proc->pid2 = last_process(proc, av, envp);
	close_pipes(proc);
	proc->counter = -1;
	waitpid(proc->pid2, &proc->error_no, 0);
	while (proc->x < ((*av)->cmd_len - 1))
	{
		waitpid(-1, 0, 0);
		proc->x++;
	}
	if (WIFEXITED(proc->error_no))
		return (WEXITSTATUS(proc->error_no));
	else if (WIFSIGNALED(proc->error_no))
		return (WTERMSIG(proc->error_no) + 128);
	return (0);
}
