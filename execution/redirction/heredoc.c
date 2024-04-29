/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:11:19 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 09:59:22 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_here_sig(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

static void	ft_child_sig(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}

static void	ft_here(char *limiter)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_here_sig);
		line = readline(">");
		i = strncmp(line, limiter, ft_strlen(limiter) + 1);
		if (i == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

static int	ft_exec_heredoc(t_redir *rec)
{
	int		pid;	

	pid = fork();
	if (pid == 0)
		ft_here(rec->filename);
	waitpid(pid, &g_exit_code, 0);
	if (WIFEXITED(g_exit_code))
		g_exit_code = WEXITSTATUS(g_exit_code);
	return (g_exit_code);
}

int	check_and_update_heredoc(t_compound *cpmd_node, t_shell *sea_shell)
{
	int		index;
	t_redir	*temp;

	(void)sea_shell;
	index = 0;
	signal(SIGQUIT, &ft_child_sig);
	signal(SIGINT, &ft_child_sig);
	while (index < cpmd_node->cmd_len)
	{
		temp = cpmd_node->s_commands[index]->redirs;
		while (temp != NULL)
		{
			if (temp->type == HEREDOC)
			{
				if (ft_exec_heredoc(temp) == 1)
					return (1);
			}
			temp = temp->next;
		}
		index++;
	}
	return (0);
}
