/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabashee <aabashee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:23 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/22 16:49:23 by aabashee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief check if the string has unmatched quotes
/// @param str 
/// @return 
bool	check_unmatched_quotes(char *str)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	while (*str)
	{
		if (*str == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*str == '"' && !single_quote)
			double_quote = !double_quote;
		str++;
	}
	return (single_quote || double_quote);
}

void	set_quote_flag(t_quote *value, char c)
{
	if (c == '\'' && value->double_q == false)
		value->single_q = !value->single_q;
	else if (c == '"' && value->single_q == false)
		value->double_q = !value->double_q;
}
/* @brief check if the string has unmatched quotes
@param str 
@return */

bool	check_line(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (false);
	if (check_unmatched_quotes(str) == true)
		return (printf("unbalanced quotes\n"), false);
	while (str[++i])
		if (!array_strchr("\t  \n\v\f\b", str[i]))
			break ;
	if (str[i] == '\0')
		return (false);
	return (true);
}
