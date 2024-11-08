/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:44:34 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/29 13:56:53 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_slash(char **args, char **env, char *cmd)
{
	int	i;
	int	slash;

	i = 0;
	slash = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
		{
			slash = 1;
			break ;
		}
		i++;
	}
	if (slash == 1)
	{
		execve(args[0], args, env);
		ft_putstr_fd("minibash: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		set_exit_status(env, 127);
		exit(127);
	}
}

int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	set_status(char **env, int x_exit_status)
{
	char	*st;

	st = ft_itoa(x_exit_status);
	set_exit_status(env, x_exit_status);
	free(st);
}

int	check_in_pwd(char **args, char **env)
{
	char	*cmd;

	cmd = ft_strjoin(get_env_var(env, "PWD"), "/");
	cmd = ft_strjoin(cmd, args[0]);
	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

void	forking_checkers(char **args, char **env, char **bins, char *cmd)
{
	if (cmd == NULL || cmd[0] == '\0')
	{
		ft_err("minibash: ", args[0], ": command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (check_in_pwd(args, env) == 1 && bins == NULL)
	{
		execve(cmd, args, env);
		exit(0);
	}
}
