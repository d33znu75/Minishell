/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:05:58 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 14:38:16 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**set_exit_status(char **env, int status)
{
	static char	*exit_status;

	exit_status = ft_itoa(status);
	env = set_env_var(env, "?", exit_status);
	free(exit_status);
	return (env);
}

char	**main_init(char **environ, char **env)
{
	if (!isatty(0))
	{
		write(1, "tty is required\n", 16);
		exit(1);
	}
	if (environ[0] == NULL)
		env = env_init_null();
	else
		env = env_init(environ);
	return (env);
}

char	**main_g_exit(char **env)
{
	if (g_exit_status == 1)
	{
		set_exit_status(env, 1);
		g_exit_status = 0;
	}
	return (env);
}

void	ctrl_d_handler(char **env)
{
	int	exit_status;

	exit_status = ft_atoi(get_env_var(env, "?"));
	write(1, "exit\n", 5);
	exit(exit_status);
	ft_malloc(0, 1);
}
