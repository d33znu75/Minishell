/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 00:23:42 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:17:56 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**add_env_var(char **env, char *var)
{
	int		i;
	char	**new_env;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)ft_malloc(sizeof(char *) * (i + 2), 0);
	if (!new_env)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_env[j] = env[j];
		j++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**set_env_var(char **env, char *var, char *value)
{
	int		i;
	int		len;
	char	**new_env;
	char	*temp_var;

	i = 0;
	len = ft_strlen(var);
	temp_var = ft_strjoin(var, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], temp_var, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			env[i] = ft_strjoin(temp_var, value);
			free(temp_var);
			return (env);
		}
		i++;
	}
	new_env = add_env_var(env, ft_strjoin(temp_var, value));
	free(temp_var);
	return (new_env);
}
