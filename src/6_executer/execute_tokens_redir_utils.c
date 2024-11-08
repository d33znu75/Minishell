/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens_redir_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:36:01 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 15:02:23 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	open_redir_file(char *filename, int flags, char **env)
{
	int		fd;
	char	*expanded_filename;

	expanded_filename = expander(filename, env);
	fd = open(expanded_filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minibash: ", STDERR_FILENO);
		ft_putstr_fd(expanded_filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		set_exit_status(env, 1);
	}
	free(expanded_filename);
	return (fd);
}

t_ast_node	*find_command_node(t_ast_node *node)
{
	while (node && node->type != TOKEN_LITERAL)
		node = node->left;
	return (node);
}

static int	set_redir_flags(t_token_type type, int **target_fd,
				int *last_in_fd, int *last_out_fd)
{
	int	flags;

	if (type == TOKEN_RDIR_IN)
	{
		flags = O_RDONLY;
		*target_fd = last_in_fd;
	}
	else
	{
		if (type == TOKEN_RDIR_OUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			flags = O_WRONLY | O_CREAT | O_APPEND;
		*target_fd = last_out_fd;
	}
	return (flags);
}

static int	handle_redir_node(t_ast_node *node, int *last_in_fd,
				int *last_out_fd, char **env)
{
	char	*filename;
	int		flags;
	int		*target_fd;
	int		fd;

	filename = handle_q(node->right->args[0]);
	flags = set_redir_flags(node->type, &target_fd, last_in_fd, last_out_fd);
	fd = open_redir_file(filename, flags, env);
	free(filename);
	if (fd == -1)
		return (0);
	if (*target_fd != -1)
		close(*target_fd);
	*target_fd = fd;
	return (1);
}

int	apply_redirections(t_ast_node *node, int *last_in_fd,
		int *last_out_fd, char **env)
{
	if (!node)
		return (1);
	if (!apply_redirections(node->left, last_in_fd, last_out_fd, env))
		return (0);
	if (node->type == TOKEN_RDIR_IN || node->type == TOKEN_RDIR_OUT
		|| node->type == TOKEN_RDIR_APPEND)
		return (handle_redir_node(node, last_in_fd, last_out_fd, env));
	return (1);
}
