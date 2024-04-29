/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:55:22 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/21 22:11:50 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	needs_expansion(char *str)
{
	t_quote	quotes;
	int		start;

	start = 0;
	quotes.single_q = false;
	quotes.double_q = false;
	while (str[start] != '\0')
	{
		set_quote_flag(&quotes, str[start]);
		if (str[start] == '$' &&!quotes.single_q
			&&!array_strchr("\" '/~+=%^{}:\t\v\f\n; '\0'", str[start + 1]))
			return (true);
		start++;
	}
	return (false);
}

int	get_search_var_end(char *str, int start)
{
	if (str[start + 1] && array_strchr("$?", str[start + 1]))
		return (start + 1);
	start++;
	while (str[start])
	{
		if (array_strchr("\" '/~+=$%^{}:\t\v\f\n; '\0'", str[start + 1]))
			break ;
		start++;
	}
	return (start);
}
// Function to find the end index of the expansion

int	get_end_index_expan(char *str, int start)
{
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	while (str[start])
	{
		set_quote_flag(&quotes, str[start]);
		if (str[start] == '$' &&!quotes.single_q
			&&!array_strchr("\" '/~+=%^{}:\t\v\f\n; '\0'", str[start + 1]))
			break ;
		start++;
	}
	return (start);
}
