/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:12:01 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 10:59:28 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_built_ins_and_exexute(t_shell *proc, t_command **av)
{
	int	ret;

	ret = 0;
	if (proc->check == 1)
		ft_exit(av, proc);
	else if (proc->check == 2)
		ft_echo(av, proc);
	else if (proc->check == 3)
		ret = ft_cd(av, proc);
	else if (proc->check == 4)
		ft_pwd(proc);
	else if (proc->check == 5)
		ft_env_print_linked(proc);
	else if (proc->check == 6)
		ret = ft_export_print_linked(av, proc);
	else if (proc->check == 7)
		ret = ft_unset(av, proc);
	exit(ret);
}

void	check_built_ins_and_exexute_one_cmd(t_shell *proc, t_command **av)
{
	if (proc->check == 1)
		ft_exit(av, proc);
	else if (proc->check == 2)
		ft_echo(av, proc);
	else if (proc->check == 3)
		ft_cd(av, proc);
	else if (proc->check == 4)
		ft_pwd(proc);
	else if (proc->check == 5)
		ft_env_print_linked(proc);
	else if (proc->check == 6)
		ft_export_print_linked(av, proc);
	else if (proc->check == 7)
		ft_unset(av, proc);
	exit(1);
}

int	ft_check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (2);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (3);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (4);
	else if (ft_strcmp(cmd, "env") == 0)
		return (5);
	else if (ft_strcmp(cmd, "export") == 0)
		return (6);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (7);
	return (0);
}

char	*get_command(t_shell *proc, char **envp, char *s)
{
	init_parsing(proc);
	if (ft_strnstr(s, "/", ft_strlen(s))
		|| ft_strcmp(s, ".") == 0 || ft_strcmp(s, "..") == 0 || s[0] == '\0')
		return (s);
	if (search(envp) == 0)
		return (NULL);
	while (envp[++proc->x])
	{
		if (ft_strncmp(envp[proc->x], "PATH=", 5) == 0)
			break ;
	}
	proc->path_split = ft_split(envp[proc->x] + 5, ':');
	proc->x = -1;
	while (proc->path_split[++proc->x] && (search(envp) == 1))
	{
		proc->path = ft_strjoin(proc->path_split[proc->x], "/");
		proc->result = ft_strjoin(proc->path, s);
		if (access(proc->result, 0) == 0)
			return (free_short(proc->path, proc->path_split), proc->result);
		safe_free(proc->path);
		safe_free(proc->result);
		proc->result = NULL;
	}
	return (free_short(NULL, proc->path_split), NULL);
}

void	ft_writing(t_command **pipe, t_shell *proc)
{
	write(2, pipe[proc->index]->cmd, ft_strlen(pipe[proc->index]->cmd));
	write(2, ": no non-numeric arguments are supported\n", 42);
	exit(255);
}
