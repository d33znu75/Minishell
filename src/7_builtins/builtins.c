/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 00:49:42 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 13:48:00 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_env_var(char **env, char *var)
{
	int		i;
	int		len;
	char	*env_var_value;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
		{
			env_var_value = ft_strdup(&env[i][len + 1]);
			return (env_var_value);
		}
		i++;
	}
	return (NULL);
}

void	ft_env(char **env)
{
	int		i;
	char	*equal;

	i = 0;
	while (env[i] != NULL)
	{
		equal = ft_strchr(env[i], '=');
		if ((ft_strncmp(env[i], "?=", 2) == 0 \
			|| ft_strncmp(env[i], "~=", 2) == 0) \
			|| equal == NULL || ft_strnstr(env[i], "/gnu/", 20))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	set_exit_status(env, 0);
}

int	check_env_var(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	if (var[0] == '$')
	{
		var++;
		len--;
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 \
			&& env[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}
