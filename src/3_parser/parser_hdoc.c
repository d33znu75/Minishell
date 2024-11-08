/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:21:47 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 15:09:00 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	heredoc_signal_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

static int	handle_heredoc_child(t_ast_node *node, int pipe_fd[2], char **env)
{
	char	*content;

	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	content = read_heredoc_content(node->delimiters, env);
	if (!content)
		exit(1);
	write(pipe_fd[1], content, ft_strlen(content));
	free(content);
	exit(EXIT_SUCCESS);
}

int	run_heredoc_process(t_ast_node *node, int pipe_fd[2], char **env)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid == 0)
		handle_heredoc_child(node, pipe_fd, env);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || (WIFEXITED(status)
			&& WEXITSTATUS(status) == 130))
	{
		close(pipe_fd[0]);
		g_exit_status = 130;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	run_heredoc(t_ast_node *node, char **env)
{
	int		pipe_fd[2];
	char	*content;

	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	if (run_heredoc_process(node, pipe_fd, env))
		return (1);
	content = read_pipe_content(pipe_fd[0]);
	close(pipe_fd[0]);
	if (!content)
		return (EXIT_FAILURE);
	free(node->heredoc_content);
	node->heredoc_content = content;
	free_delimiters_list(node->delimiters);
	node->delimiters = NULL;
	return (EXIT_SUCCESS);
}

t_ast_node	*handle_heredocs(t_token **tokens, char **env)
{
	t_ast_node	*node;
	t_token		*current;
	t_token		*last_valid;
	t_context	context;

	if (!tokens || !*tokens || (*tokens)->type != TOKEN_HDOC)
		return (NULL);
	node = init_heredoc_node();
	if (!node)
		return (NULL);
	current = *tokens;
	last_valid = *tokens;
	context = create_context(current, last_valid, env);
	if (process_heredoc_tokens(&node, tokens, &context))
		return (NULL);
	*tokens = context.current;
	return (node);
}
