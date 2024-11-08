/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 02:07:16 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 10:15:34 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_quotes(char *str)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote_count++;
		i++;
	}
	return (quote_count);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		quote_count;

	if (str == NULL)
		return (NULL);
	i = 0;
	quote_count = count_quotes(str);
	i = 0;
	j = 0;
	new_str = ft_malloc(ft_strlen(str) - quote_count + 1, 0);
	if (new_str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	check_is_in_env(char **env, char *key)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0 && \
			(env[i][ft_strlen(key)] == '=' || env[i][ft_strlen(key)] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

int	check_key_format(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=' || str[0] == '+')
		return (1);
	while (str[i + 1] != '\0' && str[i + 1] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i + 1] == '\0' && str[i] == '+')
		return (1);
	if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '+')
		return (1);
	return (0);
}

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
