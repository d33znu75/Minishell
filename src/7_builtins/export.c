/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:10:11 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:18:34 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	to_printing(int count, char **env_copy)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ft_strncmp(env_copy[i], "~=", 2) == 0 \
			|| ft_strncmp(env_copy[i], "_=", 2) == 0 \
			|| ft_strncmp(env_copy[i], "?=", 2) == 0 \
			|| ft_strnstr(env_copy[i], "/gnu/", 20))
		{
			i++;
			continue ;
		}
		write(1, "declare -x ", 11);
		env_copy[i] = add_quotes(env_copy[i]);
		ft_putstr_fd(env_copy[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

static void	to_sorting(char **env_copy, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_copy[j], env_copy[j + 1]) > 0)
				ft_swap(&env_copy[j], &env_copy[j + 1]);
			j++;
		}
		i++;
	}
	to_printing(count, env_copy);
}

static int	printing_env(char **env)
{
	int		i;
	int		count;
	char	**env_copy;

	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	env_copy = (char **)ft_malloc((count + 1) * sizeof(char *), 0);
	if (env_copy == NULL)
	{
		ft_putstr_fd("minibash: export:\n", 2);
		perror(NULL);
		set_exit_status(env, 1);
		return (1);
	}
	while (i < count)
	{
		env_copy[i] = env[i];
		i++;
	}
	env_copy[count] = NULL;
	to_sorting(env_copy, count);
	return (0);
}

char	**ft_export(char **args, char **env)
{
	int	i;
	int	exit_flag;

	exit_flag = 0;
	if (args[1] == NULL)
	{
		if (printing_env(env) == 1)
			return (env);
	}
	if (ft_strcmp(args[0], "export") == 0)
		i = 1;
	else
		i = 0;
	env = export_with_args(args, env, i, exit_flag);
	return (env);
}
