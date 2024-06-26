/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:35:15 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 17:23:55 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(t_list *head, char *str)
{
	t_list	*tmp;
	char	*tmp_val;

	tmp = head;
	tmp_val = NULL;
	if (str)
		tmp_val = ft_strjoin(str, "=");
	while (tmp)
	{
		if (ft_strcmp(tmp->key, tmp_val) == 0)
			return (safe_free(tmp_val), tmp->value);
		tmp = tmp->next;
	}
	if (tmp_val)
		safe_free(tmp_val);
	return (NULL);
}

int	create_envlist_util_2(t_exp_var *var, t_list *head, t_shell *proc,
		char **env)
{
	char	*tmp_2;

	if (ft_strncmp(env[var->x], "PWD=", 4) == 0)
	{
		var->flag_pwd = 1;
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("PWD="),
				ft_strdup(getcwd(proc->pwd, 1024)), var->x, var->x));
		var->x++;
		return (1);
	}
	else if (ft_strncmp(env[var->x], "SHLVL=", 6) == 0)
	{
		var->flag_shlvl = 1;
		tmp_2 = ft_substr(env[var->x], var->y + 1, ft_strlen(env[var->x])
				- var->y);
		ft_lstadd_back(&head, ft_lstnew(ft_substr(env[var->x], 0, var->y + 1),
				ft_itoa(ft_atoi(tmp_2) + 1), var->x, var->x));
		safe_free(tmp_2);
		var->x++;
		return (1);
	}
	return (0);
}

int	create_envlist_util(t_exp_var *var, t_list *head, t_shell *proc, char **env)
{
	if (create_envlist_util_2(var, head, proc, env) == 1)
		return (1);
	else if (ft_strncmp(env[var->x], "OLDPWD=", 7) == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("OLDPWD="),
				ft_substr(env[var->x], var->y + 1, ft_strlen(env[var->x])
					- var->y), var->x, var->x));
		var->x++;
		var->flag_oldpwd = 1;
		return (1);
	}
	else if (ft_strncmp(env[var->x], "_=", 2) == 0)
	{
		var->x++;
		return (1);
	}
	return (0);
}

void	check_and_set(t_exp_var *var, t_list *head, t_shell *proc)
{
	if (var->flag_pwd == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("PWD="),
				ft_strdup(getcwd(proc->pwd, 1024)), var->x, var->x));
		var->x++;
	}
	if (var->flag_shlvl == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("SHLVL="), ft_strdup("1"),
				var->x, var->x));
		var->x++;
	}
	if (var->flag_oldpwd == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("OLDPWD="), ft_strdup(""),
				var->x, var->x));
		var->x++;
	}
}

/**
 * create_envlist: creates a copy of the environment
 *  variable we get but in linked list form
 * @proc: the struct that contains all the variables
 * @env: the environment variable
 */
void	create_envlist(t_shell *proc, char **env)
{
	t_exp_var	var;

	init_vars(&var);
	proc->env_list = NULL;
	while (env[var.x])
	{
		if (ft_strchr(env[var.x], '='))
		{
			var.y = 0;
			while (env[var.x][var.y] && env[var.x][var.y] != '=')
				var.y++;
		}
		if (create_envlist_util(&var, proc->env_list, proc, env) == 1)
			continue ;
		ft_lstadd_back(&proc->env_list, ft_lstnew(ft_substr(env[var.x], 0, var.y
					+ 1), ft_substr(env[var.x], var.y + 1, ft_strlen(env[var.x])
					- var.y), var.x, var.x));
		var.x++;
	}
	check_and_set(&var, proc->env_list, proc);
	sort_list(proc->env_list);
	re_index(proc->env_list);
}
