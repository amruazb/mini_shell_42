/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:16:55 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 10:44:07 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_cd_util(t_command **pipe, char *pwd, t_shell *proc)
{
	char	*tmp;

	if (chdir((*pipe)->args->array[1]) == 0)
	{
		if (pwd)
		{
			tmp = ft_strjoin("OLDPWD=", pwd);
			check_and_replace(proc->env_list, tmp);
			free(tmp);
		}
		pwd = getcwd(proc->pwd, 1024);
		tmp = ft_strjoin("PWD=", pwd);
		if (pwd)
		{
			proc->x = check_and_replace(proc->env_list, tmp);
			return (free(tmp), proc->x);
		}
		ft_putstr_fd("cd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory\n", 2);
		return (1);
	}
	else
		return (write(1, (*pipe)->args->array[1],
				ft_strlen((*pipe)->args->array[1])), perror(" "), 1);
	return (0);
}

static int	ft_cd_util_3(char *pwd, t_shell *proc)
{
	char	*tmp;

	if (pwd)
	{
		tmp = ft_strjoin("OLDPWD=", pwd);
		check_and_replace(proc->env_list, tmp);
		if (tmp)
			free(tmp);
	}
	pwd = getcwd(proc->pwd, 1024);
	if (pwd)
	{
		tmp = ft_strjoin("PWD=", pwd);
		proc->x = check_and_replace(proc->env_list, tmp);
		return (safe_free(tmp), proc->x);
	}
	return (1);
}

static int	ft_cd_util_2(char *pwd, t_shell *proc)
{
	char	*tmp;

	if (chdir(ft_getenv(proc->env_list, "HOME")) == 0)
		return (ft_cd_util_3(pwd, proc));
	else
	{
		tmp = ft_getenv(proc->env_list, "HOME");
		if (tmp == NULL)
			ft_putstr_fd("cd: HOME not set\n", 2);
		else
		{
			write(2, tmp, ft_strlen(tmp));
			perror(" ");
		}
		return (safe_free(tmp), 1);
	}
	return (0);
}

int	ft_cd(t_command **pipe, t_shell *proc)
{
	char	*pwd;
	int		x;

	pwd = getcwd(proc->pwd, 1024);
	x = 0;
	if (pipe[proc->index]->args->array[1])
		x = ft_cd_util(&pipe[proc->index], pwd, proc);
	else if (pipe[proc->index]->args->array[1] == NULL)
	{
		x = ft_cd_util_2(pwd, proc);
	}
	if ((*pipe)->cmd_len > 1)
	{
		garbage_collector(&proc);
		x = 1;
	}
	return (x);
}

unsigned char	ft_small_atoi(const char *str)
{
	int						i;
	int						sign;
	unsigned char			result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (result >= UCHAR_MAX)
		return (-(sign == 1));
	return ((result * sign));
}
