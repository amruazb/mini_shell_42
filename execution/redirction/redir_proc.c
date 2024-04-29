/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:12:21 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 14:40:25 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	red_append_mode(t_redir *redir, t_shell *proc)
{
	int	file1;

	file1 = open(redir->filename, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (file1 == -1)
		terminate(redir->filename, proc);
	if (proc->dont == 0)
		dup2(file1, STDOUT_FILENO);
	close(file1);
	return (1);
}

int	red_infile(t_redir *redir, t_shell *proc)
{
	int	file1;

	file1 = open(redir->filename, O_RDONLY);
	if (file1 == -1)
		terminate(redir->filename, proc);
	if (proc->dont == 0)
		dup2(file1, STDIN_FILENO);
	close(file1);
	return (1);
}

int	red_output(t_redir *redir, t_shell *proc)
{
	int	file1;

	file1 = open(redir->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file1 == -1)
		terminate(redir->filename, proc);
	if (proc->dont == 0)
		dup2(file1, STDOUT_FILENO);
	close(file1);
	return (1);
}

void	red_middle(t_command **av, int *flag_out, int *flag_in, t_shell *proc)
{
	t_redir	*temp;

	temp = av[proc->index]->redirs;
	while (temp)
	{
		if (temp->type == OUTPUT)
			*flag_out = red_output(temp, proc);
		else if (temp->type == INPUT)
			*flag_in = red_infile(temp, proc);
		else if (temp->type == APPEND)
			*flag_out = red_append_mode(temp, proc);
		temp = temp->next;
	}
}

void	red_last_proc(t_command **av, int *flag, t_shell *proc)
{
	t_redir	*temp;

	temp = av[proc->index]->redirs;
	while (temp)
	{
		proc->index = (*av)->cmd_len - 1;
		if (temp->type == OUTPUT)
			red_output(temp, proc);
		else if (temp->type == INPUT)
			*flag = red_infile(temp, proc);
		else if (temp->type == APPEND)
			red_append_mode(temp, proc);
		temp = temp->next;
	}
}
