/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:27:46 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 22:17:55 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_chars(char *str)
{
	int		i;
	int		count;
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	i = -1;
	count = 0;
	while (str[++i])
	{
		set_quote_flag(&quotes, str[i]);
		if ((str[i] == '"' && !quotes.single_q)
			|| (str[i] == '\'' && !quotes.double_q))
			continue ;
		count++;
	}
	return (count);
}

char	*remove_quotes(char *str, int in)
{
	char	*new_str;
	int		i;
	int		j;
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	i = -1;
	j = 0;
	new_str = (char *)malloc(sizeof(char *) * (count_chars(str) + 1));
	while (str[++i])
	{
		set_quote_flag(&quotes, str[i]);
		if ((str[i] == '"' && !quotes.single_q)
			|| (str[i] == '\'' && !quotes.double_q))
			continue ;
		new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	if (in == 1)
		safe_free(str);
	return (new_str);
}

void	token_quote_removal(t_token *tokenlist)
{
	t_token	*temp;

	temp = tokenlist;
	while (temp)
	{
		if (temp->type == REDIR
			&& ft_strcmp(temp->value, "<<") == 0 && temp->next)
		{
			temp = temp->next->next;
			continue ;
		}
		if (temp->type == WORD)
			temp->value = remove_quotes(temp->value, 1);
		temp = temp->next;
	}
}

t_token_type	assign_t_token_type(char *arg)
{
	t_token_type	type;

	if (ft_strcmp(arg, "<") == 0)
		type = REDIR;
	else if (ft_strcmp(arg, ">") == 0)
		type = REDIR;
	else if (ft_strcmp(arg, ">>") == 0)
		type = REDIR;
	else if (ft_strcmp(arg, "<<") == 0)
		type = REDIR;
	else if (ft_strcmp(arg, "|") == 0)
		type = PIPE;
	else if (ft_strcmp(arg, "&&") == 0)
		type = AND;
	else if (ft_strcmp(arg, "||") == 0)
		type = OR;
	else if (ft_strcmp(arg, "(") == 0)
		type = OPEN_PAREN;
	else if (ft_strcmp(arg, ")") == 0)
		type = CLOSE_PAREN;
	else
		type = WORD;
	return (type);
}
