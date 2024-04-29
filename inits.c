/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:57:57 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 17:22:38 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_sea_shell(t_shell *sea_shell)
{
	sea_shell->env_vars = NULL;
	sea_shell->isfreed = false;
	sea_shell->line = NULL;
	sea_shell->tokenlist = NULL;
	sea_shell->split_on = PIPE;
	sea_shell->cmpd_node = NULL;
	sea_shell->dont = 0;
	sea_shell->temp_list = NULL;
	sea_shell->result = NULL;
}

void	init_sea_shell_exec(int ac, t_shell *sea_shell)
{
	sea_shell->middle_scommand = ac - 2;
	sea_shell->total_pipes = ac - 1;
	sea_shell->counter = 0;
	sea_shell->env_vars = linked_to_array(sea_shell->env_list);
	if (!sea_shell->env_vars)
	{
		garbage_collector(&sea_shell);
		exit(printf("Error: No environment variables found\n"));
	}
}

void	init_parsing(t_shell *proc)
{
	proc->x = -1;
	proc->temp_list = proc->env_list;
	proc->path = NULL;
	proc->result = NULL;
}
/*
* @brief initialize the prompt
@param sea_shell structure for the shell  */

void	init_prompt(t_shell *sea_shell)
{
	sea_shell->line = readline(B"minishell$ "RST);
	if (!sea_shell->line)
		free_and_exit(sea_shell, "exit");
}

void	init_vars(t_exp_var *var)
{
	var->flag_pwd = 0;
	var->x = 0;
	var->y = 0;
	var->flag_shlvl = 0;
	var->flag_oldpwd = 0;
}
