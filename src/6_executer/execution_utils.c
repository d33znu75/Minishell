/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:22:38 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/09/28 16:04:16 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_arglen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_strcasecmp(const char *s1, const char *s2)
{
	while (*s1 && (ft_tolower(*s1) == ft_tolower(*s2)))
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*(const unsigned char *)s1) - \
	ft_tolower(*(const unsigned char *)s2));
}

int	only_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_the_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)ft_malloc(sizeof(char) * ft_strlen(str) + 1, 0);
	while (str[i] != '\0')
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
