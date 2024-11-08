/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:24:56 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/25 16:21:51 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	has_syntax_error(char *cmd_line, char **env)
{
	if (has_mismatched_quotes(cmd_line) == true)
	{
		ft_putstr_fd(UNCLOSED_QUOTES, STDERR_FILENO);
		set_exit_status(env, 258);
		return (1);
	}
	if (has_misplaced_pipes(cmd_line) == true)
	{
		ft_putstr_fd(MISPLACED_PIPE, STDERR_FILENO);
		set_exit_status(env, 258);
		return (1);
	}
	if (has_unsupported_operators(cmd_line))
	{
		ft_putstr_fd(UNSUPPORTED_OPERATORS, STDERR_FILENO);
		set_exit_status(env, 258);
		return (1);
	}
	return (0);
}
