/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:15:17 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:00:38 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_key_format_2(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (1);
	while (str[i + 1] != '\0' && str[i + 1] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i + 1] == '\0' && str[i] == '+')
		return (1);
	if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		return (1);
	return (0);
}

static void	shift_env_vars(char **env, int j)
{
	while (env[j] != NULL)
	{
		env[j] = env[j + 1];
		j++;
	}
}

static char	**unset_env_var(char **args, char **env)
{
	int		j;
	size_t	len;

	len = ft_strlen(*args);
	j = 0;
	while (env[j] != NULL)
	{
		if (ft_strncmp(env[j], *args, len) == 0 \
			&& (env[j][len] == '=' || env[j][len] == '\0'))
		{
			free(env[j]);
			shift_env_vars(env, j);
			break ;
		}
		j++;
	}
	return (env);
}

char	**ft_unset(char **args, char **env)
{
	int	exit_flag;

	exit_flag = 0;
	while (*args != NULL)
	{
		if (check_key_format_2(*args) == 1)
		{
			ft_putstr_fd("minibash: unset: `", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_flag = 1;
		}
		env = unset_env_var(args, env);
		args++;
	}
	if (exit_flag == 1)
		env = set_env_var(env, "?", "1");
	else
		env = set_env_var(env, "?", "0");
	return (env);
}
