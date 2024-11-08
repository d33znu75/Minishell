/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_checker_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:25:38 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/02 17:17:18 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	has_mismatched_quotes(char *cmd_line)
{
	bool	in_single_quote;
	bool	in_double_quote;

	1 && (in_single_quote = false, in_double_quote = false);
	while (*cmd_line)
	{
		if (*cmd_line == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*cmd_line == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		cmd_line++;
	}
	return (in_single_quote || in_double_quote);
}

bool	has_misplaced_pipes(char *cmd_line)
{
	bool	expecting_expression;
	bool	s_quote_open;
	bool	d_quote_open;

	expecting_expression = false;
	1 && (s_quote_open = false, d_quote_open = false);
	if (*cmd_line == '|')
		return (true);
	while (*cmd_line)
	{
		if (*cmd_line == '\'')
			s_quote_open = !s_quote_open;
		else if (*cmd_line == '\"')
			d_quote_open = !d_quote_open;
		if (*cmd_line == '|' && !s_quote_open && !d_quote_open)
		{
			if (expecting_expression == true)
				return (true);
			expecting_expression = true;
		}
		else if (!ft_isspace(*cmd_line))
			expecting_expression = false;
		cmd_line++;
	}
	return (expecting_expression);
}

static bool	check_operator(char **cmd_line)
{
	if (**cmd_line == '&')
		return (true);
	if (**cmd_line == '|' && *(*cmd_line + 1) == '|')
		return (true);
	if (**cmd_line == ';' || **cmd_line == '(' || **cmd_line == ')')
		return (true);
	return (false);
}

bool	has_unsupported_operators(char *cmd_line)
{
	bool	s_quote_open;
	bool	d_quote_open;

	s_quote_open = false;
	d_quote_open = false;
	while (*cmd_line)
	{
		if (*cmd_line == '\'' && !d_quote_open)
			s_quote_open = !s_quote_open;
		else if (*cmd_line == '\"' && !s_quote_open)
			d_quote_open = !d_quote_open;
		if (!s_quote_open && !d_quote_open)
		{
			if (check_operator(&cmd_line))
				return (true);
		}
		cmd_line++;
	}
	return (false);
}
