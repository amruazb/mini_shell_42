/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_proc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:40:04 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 14:40:10 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	red_first_proc(t_command **av, int *flag, t_shell *proc)
{
	t_redir	*temp;

	temp = av[0]->redirs;
	while (temp)
	{
		if (temp->type == OUTPUT)
			*flag = red_output(temp, proc);
		else if (temp->type == INPUT)
			red_infile(temp, proc);
		else if (temp->type == APPEND)
			*flag = red_append_mode(temp, proc);
		temp = temp->next;
	}
}

void	red_one_cmd(t_command **av, t_shell *proc)
{
	t_redir	*temp;

	temp = av[proc->index]->redirs;
	while (temp)
	{
		if (temp->type == OUTPUT)
			red_output(temp, proc);
		else if (temp->type == INPUT)
			red_infile(temp, proc);
		else if (temp->type == APPEND)
			red_append_mode(temp, proc);
		temp = temp->next;
	}
}
