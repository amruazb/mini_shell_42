/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:19:08 by shmuhamm          #+#    #+#             */
/*   Updated: 2024/04/23 16:59:19 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	checkenv(char **envp)
{
	if (!envp || envp[0] == NULL)
	{
		printf("Error: No Env found\n");
		exit(EXIT_FAILURE);
	}
}

int	ft_token_count(char **str)
{
	int	token_counts;

	token_counts = 0;
	if (!str)
		return (0);
	while (str[token_counts])
		token_counts++;
	return (token_counts);
}

void	checkargs(int ac, char **av)
{
	if (ac > 1 || ft_token_count(av) > 1)
	{
		write(2, "usage <./minishell>", 19);
		exit(EXIT_FAILURE);
	}
}

t_shell	*allocateshell(void)
{
	t_shell	*sea_shell;

	sea_shell = malloc(sizeof(t_shell));
	if (!sea_shell)
	{
		write(2, "Memory allocation failure\n", 26);
		exit(EXIT_FAILURE);
	}
	return (sea_shell);
}

void	free_and_exit(t_shell *sea_shell, char *message)
{
	garbage_collector(&sea_shell);
	exit(printf("%s\n", message));
}
