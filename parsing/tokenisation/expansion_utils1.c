/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:11:22 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 22:11:24 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*strjoin_new_var(char *temp_str, char *expanded_str, int count)
{
	char	*temp;

	temp = NULL;
	if (count > 1 && expanded_str)
	{
		temp = ft_strjoin(expanded_str, temp_str);
		if (temp)
			safe_free(expanded_str);
	}
	else
		temp = ft_strdup(temp_str);
	if (temp)
		safe_free(temp_str);
	return (temp);
}
// Function to retrieve the value of an environment variable

static char	*get_env_var(t_shell *sea_shell, char *str, int start)
{
	char	*search_var;
	char	*env_var;
	char	*envv;

	env_var = NULL;
	search_var = ft_substr(str,
			start + 1, get_search_var_end(str, start) - start);
	if (search_var && search_var[0] == '?' && search_var[1] == '\0')
		env_var = ft_itoa(g_exit_code);
	else
	{
		envv = ft_getenv(sea_shell->env_list, search_var);
		if (envv)
			env_var = ft_strdup(envv);
		else
			env_var = ft_strdup("");
	}
	if (env_var == NULL)
	{
		safe_free(search_var);
		return (ft_strdup(""));
	}
	if (search_var)
		safe_free(search_var);
	return (env_var);
}

char	*new_expanded_str(t_shell *sea_shell, char *str)
{
	int		i;
	char	*expanded_str;
	char	*temp_str;
	int		count;

	i = 0;
	count = 0;
	expanded_str = NULL;
	temp_str = NULL;
	while (str[i] && ++count)
	{
		if (str[i] == '$'
			&& !array_strchr("\" '/~+=%^{}:\t\v\f\n; '\0'", str[i + 1]))
		{
			temp_str = get_env_var(sea_shell, str, i);
			i = get_search_var_end(str, i) + 1;
		}
		else
		{
			temp_str = ft_substr(str, i, get_end_index_expan(str, i) - i);
			i = get_end_index_expan(str, i);
		}
		expanded_str = strjoin_new_var(temp_str, expanded_str, count);
	}
	return (expanded_str);
}
