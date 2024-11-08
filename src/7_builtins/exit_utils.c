/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:33:12 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/02 17:06:23 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	exit_with_error(char *arg, char **env)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minibash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	set_exit_status(env, 255);
	exit(255);
	ft_malloc(0, 1);
}

void	exit_max_long(char **args, char **env)
{
	char	*check;

	check = ft_strndup(args[1], 6);
	if (ft_atoi2(check) > 922337)
		exit_with_error(args[1], env);
	free(check);
	check = ft_strndup(args[1] + 6, 6);
	if (ft_atoi2(check) > 203685)
		exit_with_error(args[1], env);
	free(check);
	check = ft_strndup(args[1] + 12, 7);
	if (ft_atoi2(check) > 4775807)
	{
		free(check);
		exit_with_error(args[1], env);
	}
}

void	exit_min_long(char **args, char **env)
{
	char	*check;

	check = ft_strndup(args[1] + 1, 6);
	if (ft_atoi2(check) > 922337)
		exit_with_error(args[1], env);
	free(check);
	check = ft_strndup(args[1] + 7, 6);
	if (ft_atoi2(check) > 203685)
		exit_with_error(args[1], env);
	free(check);
	check = ft_strndup(args[1] + 13, 7);
	if (ft_atoi2(check) > 4775808)
	{
		free(check);
		exit_with_error(args[1], env);
	}
}
