/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens_redir_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:36:06 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 14:46:07 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	setup_redirections(int last_in_fd, int last_out_fd)
{
	if (last_in_fd != -1)
	{
		dup2(last_in_fd, STDIN_FILENO);
		close(last_in_fd);
	}
	if (last_out_fd != -1)
	{
		dup2(last_out_fd, STDOUT_FILENO);
		close(last_out_fd);
	}
}

void	restore_std_fds(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	handle_redir(t_ast_node *node, char **env, int *s_save)
{
	int			last_in_fd;
	int			last_out_fd;
	t_ast_node	*cmd_node;
	int			saved_in;
	int			saved_out;

	last_in_fd = -1;
	last_out_fd = -1;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	cmd_node = find_command_node(node);
	if (apply_redirections(node, &last_in_fd, &last_out_fd, env))
	{
		setup_redirections(last_in_fd, last_out_fd);
		if (cmd_node)
			execute_ast(cmd_node, env, s_save);
	}
	restore_std_fds(saved_in, saved_out);
}
