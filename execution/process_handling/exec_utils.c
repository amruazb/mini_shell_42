/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:24:34 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 09:54:49 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	one_cmd_process(t_shell *proc, t_command **av, char **envp)
{
	char	*tmp;

	proc->process_id = fork();
	if (proc->process_id < 0)
		terminate("fork", proc);
	if (proc->process_id == 0)
	{
		if ((*av)->total_redirs > 0)
			red_one_cmd(av, proc);
		if ((*av)->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin((*av)->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute_one_cmd(proc, av);
		tmp = get_command(proc, envp, (*av)->cmd);
		check_and_execute(proc, av, envp, tmp);
	}
}

int	set_signal_exe(t_command **av, t_shell *proc, char **envp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
	one_cmd_process(proc, av, envp);
	waitpid(-1, &proc->error_no, 0);
	if (WIFEXITED(proc->error_no))
		return (WEXITSTATUS(proc->error_no));
	else if (WIFSIGNALED(proc->error_no))
		return (WTERMSIG(proc->error_no) + 128);
	return (0);
}

int	pipex_one_cmd(t_command **av, t_shell *proc, char **envp)
{
	proc->index = 0;
	if (av[0]->cmd && ft_strcmp(av[0]->cmd, "cd") == 0)
		return (do_operation(proc, av), ft_cd(av, proc));
	else if (av[0]->cmd && ft_strcmp(av[0]->cmd,
			"exit") == 0 && proc->paren == 2)
	{
		do_operation(proc, av);
		ft_exit(av, proc);
		return (1);
	}
	else if (av[0]->cmd && ft_strcmp(av[0]->cmd, "unset") == 0)
		return (do_operation(proc, av), ft_unset(av, proc));
	else if (av[0]->cmd && ft_strcmp(av[0]->cmd, "export") == 0)
		return (do_operation(proc, av), ft_export_print_linked(av, proc));
	else
		return (set_signal_exe(av, proc, envp));
	return (0);
}

int	pipex(int ac, t_command **scommand, t_shell *sea_shell)
{
	int	counter;
	int	ret;

	ret = 0;
	counter = -1;
	init_sea_shell_exec(ac, sea_shell);
	if (ac > 1)
		while (++counter < ac - 1)
			pipe(sea_shell->fd[counter]);
	if (ac == 1)
		ret = pipex_one_cmd(scommand, sea_shell, sea_shell->env_vars->array);
	else if (ac == 2)
	{
		ret = pipex_two_cmd(scommand, sea_shell, sea_shell->env_vars->array);
	}
	else if (ac > 2)
		ret = pipex_three_cmd(scommand, sea_shell, sea_shell->env_vars->array);
	else
		printf("Error : no command input\n");
	if (sea_shell->env_vars)
		free_t_char(&sea_shell->env_vars);
	return (ret);
}

bool	start_execution(t_compound *cpmd_node, t_shell *sea_shell)
{
	if (cpmd_node->cmd_len >= 220)
	{
		ft_putstr_fd("Sorry too many commands\n", 2);
		g_exit_code = 1;
		return (false);
	}
	if (check_and_update_heredoc(cpmd_node, sea_shell))
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sig_handler);
	g_exit_code = pipex(cpmd_node->cmd_len, cpmd_node->s_commands, sea_shell);
	unlink(".tmp");
	return (false);
}
