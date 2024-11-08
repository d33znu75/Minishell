/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:38:29 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 14:38:17 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	exec_pid1(int *fd, t_ast_node *node, char **env, int *s_save)
{
	char	*env_var;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_ast(node->left, env, s_save);
	env_var = get_env_var(env, "?");
	if (env_var == NULL)
		exit(0);
	exit(ft_atoi(env_var));
}

static void	exec_pid2(int *fd, t_ast_node *node, char **env, int *s_save)
{
	char	*env_var;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_ast(node->right, env, s_save);
	env_var = get_env_var(env, "?");
	if (env_var == NULL)
		exit(0);
	exit(ft_atoi(env_var));
}

void	token_pipe(t_ast_node *node, char **env, int *s_save)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	signal(SIGINT, handle_sigpipe);
	if (pipe(fd) == -1)
		return (set_exit_status(env, 1), perror("minibash: pipe"));
	pid1 = fork();
	if (pid1 == 0)
		exec_pid1(fd, node, env, s_save);
	else if (pid1 < 0)
		return (set_exit_status(env, 1), perror("minibash: fork"));
	pid2 = fork();
	if (pid2 == 0)
		exec_pid2(fd, node, env, s_save);
	else if (pid2 < 0)
		return (set_exit_status(env, 1), perror("minibash: fork"));
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		set_status(env, WEXITSTATUS(status));
}
