/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:58:26 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/02 17:06:08 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	void	exit_checker_1(char **args, char **env)
{
	int	i;

	i = 0;
	if (ft_arglen(args) > 2)
	{
		if (args[1][i] == '-' || args[1][i] == '+')
			i++;
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]) == 0)
				exit_with_error(args[1], env);
			i++;
		}
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minibash: exit: too many arguments\n", 2);
		set_exit_status(env, 1);
		return ;
	}
	if (ft_arglen(args) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
		ft_malloc(0, 1);
	}
}

static	int	exit_and_sign(char **args, char **env)
{
	int		i;
	int		nega;
	char	*num;

	i = 0;
	nega = 0;
	if (args[1][i] == '-')
	{
		nega = 1;
		i++;
	}
	if (args[1][i] == '+')
		i++;
	num = ft_strtrim(args[1], " ");
	while (num[i])
	{
		if (ft_isdigit(num[i]) == 0)
			exit_with_error(args[1], env);
		i++;
	}
	return (nega);
}

static	void	exit_checker_2(char **args, char **env)
{
	int	nega;

	nega = exit_and_sign(args, env);
	if (ft_strlen(args[1]) > 19 && nega == 0)
		exit_with_error(args[1], env);
	if (ft_strlen(args[1]) > 20 && nega == 1)
		exit_with_error(args[1], env);
	if (ft_strlen(args[1]) == 19 && nega == 0)
		exit_max_long(args, env);
	if (ft_strlen(args[1]) == 20 && nega == 1)
		exit_min_long(args, env);
}

void	ft_exit(char **args, char **env)
{
	if (ft_arglen(args) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
		ft_malloc(0, 1);
	}
	exit_checker_1(args, env);
	if (ft_arglen(args) == 2)
	{
		exit_checker_2(args, env);
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(args[1]));
		ft_malloc(0, 1);
	}
}
