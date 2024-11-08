/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 09:29:36 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/08 08:20:37 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	execute_hdoc_child(t_ast_node *node, int *pipefd, char **env)
{
	(void)env;
	close(pipefd[0]);
	while (node && node->type == TOKEN_HDOC)
	{
		write(pipefd[1], node->heredoc_content,
			ft_strlen(node->heredoc_content));
		node = node->left;
	}
	close(pipefd[1]);
	exit(0);
}

void	execute_hdoc_command3(t_ast_node *node, char **env, int saved_stdin)
{
	t_ast_node	*tmp;

	tmp = node->left;
	while (tmp && tmp->type != TOKEN_LITERAL)
		tmp = tmp->left;
	if (tmp && tmp->type == TOKEN_LITERAL)
		execute_command(tmp, env, 0, 0);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	execute_hdoc_command(t_ast_node *node, char **env, int saved_stdin)
{
	t_ast_node	*tmp;

	tmp = node->left;
	while (tmp && tmp->type != TOKEN_LITERAL)
		tmp = tmp->left;
	if (tmp && tmp->type == TOKEN_LITERAL)
		execute_command(tmp, env, 0, 0);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	execute_hdoc(t_ast_node *node, char **env)
{
	int		pipefd[2];
	int		saved_stdin;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (ft_putstr_fd(HDOC_PIPE_ERROR, STDERR_FILENO));
	1 && (saved_stdin = dup(STDIN_FILENO), pid = fork());
	if (pid == -1)
	{
		ft_putstr_fd(HDOC_FORK_ERROR, STDERR_FILENO);
		1 && (close(pipefd[0]), close(pipefd[1]));
		return ;
	}
	if (pid == 0)
		execute_hdoc_child(node, pipefd, env);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
		execute_hdoc_command(node, env, saved_stdin);
	}
}
