/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:10:47 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:18:18 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**append_env(int j, char *key, char *value, char **env)
{
	char	*new_value;
	char	*temp2;
	char	*temp3;
	char	*temp4;
	char	*temp[2];

	j = j + 2;
	value = ft_substr(value, j, ft_strlen(value) - j);
	new_value = remove_quotes(value);
	if (check_is_in_env(env, key) == 0)
		env = add_env_var(env, ft_strjoin(ft_strjoin(key, "="), new_value));
	else if (check_is_in_env(env, key) == 1)
	{
		temp[0] = key;
		temp[1] = NULL;
		temp2 = ft_strjoin(get_env_var(env, key), new_value);
		temp3 = ft_strjoin(key, "=");
		temp4 = ft_strjoin(temp3, temp2);
		env = ft_unset(temp, env);
		env = add_env_var(env, temp4);
	}
	free(new_value);
	free(value);
	return (env);
}

char	**ft_export_plus(char **args, char **env)
{
	int		i;
	int		j;
	char	*key;

	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0' && args[i][j] != '+')
			j++;
		key = ft_substr(args[i], 0, j);
		if (args[i][j] == '+')
			env = append_env(j, key, args[i], env);
		free(key);
		i++;
	}
	set_exit_status(env, 0);
	return (env);
}
