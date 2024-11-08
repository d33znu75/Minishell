/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:23:18 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 11:39:27 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	void	export_exit_status(char **env, int exit_flag)
{
	if (exit_flag == 1)
		set_exit_status(env, 1);
	else
		set_exit_status(env, 0);
}

static	char	**add_to_env(char **env, char *key, int j, char *args)
{
	char	*value;
	char	*value_final;
	char	*temp[2];

	j++;
	value = ft_substr(args, j, ft_strlen(args) - j);
	value_final = ft_strjoin(ft_strjoin(key, "="), value);
	if (check_is_in_env(env, key) == 0)
		env = add_env_var(env, value_final);
	else if (check_is_in_env(env, key) == 1)
	{
		temp[0] = key;
		temp[1] = NULL;
		env = ft_unset(temp, env);
		env = add_env_var(env, value_final);
	}
	return (env);
}

char	**export_with_args(char **args, char **env, int i, int exit_flag)
{
	char	*key;
	int		j;

	while (args[i] != NULL)
	{
		if (check_key_format(args[i]) == 1)
		{
			ft_err("minibash: export: ", args[i], EXP_ERR, 2);
			1 && (exit_flag = 1, i++);
			continue ;
		}
		j = 0;
		while (args[i][j] != '\0' && args[i][j] != '=')
			j++;
		if (args[i][j] == '=' && j != 0 && args[i][j - 1] == '+')
			return (env = ft_export_plus(args, env), env);
		key = ft_substr(args[i], 0, j);
		if (args[i][j] == '=')
			env = add_to_env(env, key, j, args[i]);
		else
			if (check_is_in_env(env, key) == 0)
				env = add_env_var(env, key);
		i++;
	}
	return (export_exit_status(env, exit_flag), env);
}
