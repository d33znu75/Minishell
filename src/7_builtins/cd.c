/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:08:45 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/03 01:19:41 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**ft_cd_home(char **args, char **env)
{
	if (check_env_var(env, "HOME") == 0)
	{
		ft_putstr_fd("minibash: cd: HOME not set\n", 2);
		set_exit_status(env, 1);
		return (env);
	}
	args[1] = get_env_var(env, "HOME");
	if (chdir(args[1]) == 0)
	{
		env = ft_unset((char *[]){"OLDPWD", NULL}, env);
		env = set_env_var(env, "OLDPWD", get_env_var(env, "PWD"));
		env = set_env_var(env, "PWD", ft_pwd_str(env));
		set_exit_status(env, 0);
		return (env);
	}
	else
	{
		set_exit_status(env, 1);
		ft_err("minibash: ", args[1], FILE_NOT_FOUND, STDERR_FILENO);
		return (env);
	}
	return (env);
}

char	**ft_cd_tilde1(char **args, char **env)
{
	args[1] = remove_quotes(args[1]);
	if (chdir(get_env_var(env, "~")) == 0)
	{
		env = ft_unset((char *[]){"OLDPWD", NULL}, env);
		env = set_env_var(env, "OLDPWD", get_env_var(env, "PWD"));
		env = set_env_var(env, "PWD", ft_pwd_str(env));
		set_exit_status(env, 0);
		return (env);
	}
	else
	{
		set_exit_status(env, 1);
		ft_err("minibash: ", args[1], FILE_NOT_FOUND, STDERR_FILENO);
		return (env);
	}
}

char	**ft_cd_tilde2(char **args, char **env)
{
	char	*home;
	char	*path;

	args[1] = remove_quotes(args[1]);
	if (check_env_var(env, "HOME") == 1)
		home = get_env_var(env, "HOME");
	else
		home = get_env_var(env, "~");
	path = ft_strjoin(home, args[1] + 1);
	if (chdir(path) == 0)
	{
		env = ft_unset((char *[]){"OLDPWD", NULL}, env);
		env = set_env_var(env, "OLDPWD", get_env_var(env, "PWD"));
		env = set_env_var(env, "PWD", ft_pwd_str(env));
		set_exit_status(env, 0);
		return (env);
	}
	else
	{
		set_exit_status(env, 1);
		ft_err("minibash: ", args[1], FILE_NOT_FOUND, STDERR_FILENO);
		return (env);
	}
}

char	**ft_cd(char **args, char **env)
{
	args[1] = remove_quotes(args[1]);
	if (args[1] == NULL || ft_strcmp(args[1], "--") == 0)
		return (ft_cd_home(args, env));
	else if (ft_strncmp(args[1], "~", 1) == 0 && args[1][1] == '\0')
		return (ft_cd_tilde1(args, env));
	else if (ft_strncmp(args[1], "~/", 2) == 0)
		return (ft_cd_tilde2(args, env));
	else if (chdir(args[1]) == 0)
	{
		env = ft_unset((char *[]){"OLDPWD", NULL}, env);
		env = set_env_var(env, "OLDPWD", get_env_var(env, "PWD"));
		env = set_env_var(env, "PWD", ft_pwd_str(env));
		set_exit_status(env, 0);
		return (env);
	}
	else
	{
		set_exit_status(env, 1);
		ft_err("minibash: ", args[1], FILE_NOT_FOUND, STDERR_FILENO);
		return (env);
	}
}
