/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:39:07 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 14:15:37 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	void	ft_stat(char *cmd, char **args, char **env, struct stat s)
{
	if (S_ISDIR(s.st_mode) && has_slash(args[0]) == 1)
	{
		ft_err("minibash: ", cmd, ": is a directory\n", STDERR_FILENO);
		set_exit_status(env, 126);
		exit(126);
	}
	else if (S_ISREG(s.st_mode) && access(cmd, X_OK) == 0 \
		&& has_slash(args[0]) == 1)
	{
		execve(cmd, args, env);
		exit(0);
	}
	if (has_slash(args[0]) == 1)
	{
		ft_err("minibash: ", cmd, ": Permission denied\n", STDERR_FILENO);
		set_exit_status(env, 126);
		exit(126);
	}
}

static	int	handle_dir(char **env, char **args)
{
	struct stat	s;
	char		*cmd;

	if (args[0][0] == '~' && getenv("HOME") != NULL)
		cmd = ft_strjoin(getenv("HOME"), &args[0][1]);
	else
		cmd = ft_strdup(args[0]);
	if (ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
	{
		ft_err("minibash: ", cmd, ": command not found\n", STDERR_FILENO);
		return (set_exit_status(env, 127), 1);
	}
	if (stat(cmd, &s) == 0)
	{
		ft_stat(cmd, args, env, s);
		free(cmd);
		return (0);
	}
	return (free(cmd), 0);
}

static	void	forking(char **bins, char **args, char **env)
{
	char	*cmd;
	char	*path;

	if (handle_dir(env, args) == 1)
		exit(127);
	cmd = args[0];
	handle_slash(args, env, cmd);
	forking_checkers(args, env, bins, cmd);
	while (*bins)
	{
		path = ft_strjoin(*bins, "/");
		cmd = ft_strjoin(path, args[0]);
		if (access(cmd, F_OK | X_OK) == 0)
		{
			execve(cmd, args, env);
			exit(EXIT_FAILURE);
		}
		bins++;
	}
	ft_err("minibash: ", args[0], ": command not found\n", STDERR_FILENO);
	exit(127);
}

static	void	wait_status(pid_t pid, int status, char **env)
{
	int		exit_status;
	int		x_exit_status;

	exit_status = 0;
	x_exit_status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		x_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_status = WTERMSIG(status);
		if (exit_status == SIGINT)
		{
			x_exit_status = 130;
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		else if (exit_status == SIGKILL)
			x_exit_status = 137;
		else if (exit_status == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
			x_exit_status = 131;
		}
	}
	set_status(env, x_exit_status);
}

char	**execute_command_in_bin(char **args, char **env)
{
	pid_t	pid;
	char	**bins;
	int		status;

	status = 0;
	bins = ft_split2(get_env_var(env, "PATH"), ':');
	if (bins == NULL && has_slash(args[0]) == 0 && check_in_pwd(args, env) == 0)
	{
		ft_err("minibash: ", args[0], FILE_NOT_FOUND, STDERR_FILENO);
		return (set_exit_status(env, 127), env);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minibash: fork");
		set_exit_status(env, 1);
		exit(1);
	}
	if (pid == 0)
		forking(bins, args, env);
	else
		wait_status(pid, status, env);
	return (env);
}
