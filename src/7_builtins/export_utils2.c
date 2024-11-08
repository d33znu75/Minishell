/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:13:20 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/09/24 23:10:02 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_value_in_env(char **env, char *value)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0' && env[i][j] != '=')
			j++;
		if (ft_strncmp(&env[i][j + 1], value, ft_strlen(value) - 1) == 0)
			count++;
		i++;
	}
	return (count);
}

char	*create_new_str_with_quotes(char *str, int st, int i)
{
	char	*new_str;
	int		j;

	j = 0;
	new_str = ft_malloc(i + 3, 0);
	if (new_str == NULL)
		return (NULL);
	while (str[j] != '=')
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = '=';
	new_str[j + 1] = '\"';
	j = j + 2;
	i = st;
	while (str[i] != '\0')
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\"';
	new_str[j + 1] = '\0';
	return (new_str);
}

char	*add_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		st;
	char	*equals;

	i = 0;
	equals = ft_strchr(str, '=');
	if (equals)
	{
		while (str[i] != '=')
			i++;
		i++;
		st = i;
		while (str[i] != '\0')
			i++;
		new_str = create_new_str_with_quotes(str, st, i);
		if (new_str == NULL)
			return (NULL);
	}
	else
		return (str);
	return (new_str);
}
