/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:37 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 11:06:19 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
 * sig_handler: a function to handle signal calls
 * @num: number of the signal status
 * This function handles signal calls and is triggered when a signal is received.
 * If the signal number is SIGINT, it clears the current line, prints a newline,
 * and sets the global error status to 1.
 */
void	sig_handler(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
}
/**
 * child_sig_handler: a function to handle signal calls in child processes
 * @num: number of the signal status
 *
 * This function handles signal calls in child processes and is triggered when a
 * signal is received. If the signal number is SIGINT, it prints a newline and
 * sets the global error status to 130. If the signal number is SIGQUIT, it
 * prints "Quit: 3" and sets the global error status to 130.
 */

void	child_sig_handler(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_exit_code = 130;
	}
	else if (num == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_exit_code = 130;
	}
}
/**
 * do_operation: a function to execute a command with redirections
 * @proc: a pointer to a t_shell struct representing the shell process

* @av: a double pointer to a t_command struct representing the command to execute
 *

* This function executes a command with redirections. It sets the 'dont' field of
 * the t_shell struct to 1, indicating that the command should not be forked. If
 * the command has any redirections, it calls the red_one_cmd function to handle
 * them.
 */

void	do_operation(t_shell *proc, t_command **av)
{
	proc->dont = 1;
	if ((*av)->total_redirs > 0)
		red_one_cmd(av, proc);
}
/**
 * init_signals: a function to initialize signal handlers
 *
 * This function initializes signal handlers for the SIGINT and SIGQUIT signals.
 * The SIGINT signal is handled by the sig_handler function, and the SIGQUIT
 * signal is ignored.
 */

void	init_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
