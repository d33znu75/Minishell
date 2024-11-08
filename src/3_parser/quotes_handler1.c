/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:23:12 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:15:45 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	char	*handle_single_quote(char *str, int *i, char *new_str, int *j)
{
	(*i)++;
	while (str[*i] != '\'' && str[*i] != '\0')
	{
		new_str[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (new_str);
}

static	char	*handle_double_quote(char *str, int *i, char *new_str, int *j)
{
	(*i)++;
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		new_str[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str[*i] == '\"')
		(*i)++;
	return (new_str);
}

static	char	*handle_no_quote(char *str, int *i, char *new_str, int *j)
{
	new_str[*j] = str[*i];
	(*j)++;
	(*i)++;
	return (new_str);
}

char	*handle_q(char *str)
{
	int		i;
	int		len;
	int		j;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	new_str = (char *)ft_malloc(sizeof(char) * (len + 1), 0);
	if (!new_str)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		if (str[i] == '\'')
			new_str = handle_single_quote(str, &i, new_str, &j);
		else if (str[i] == '\"')
			new_str = handle_double_quote(str, &i, new_str, &j);
		else
			new_str = handle_no_quote(str, &i, new_str, &j);
	}
	new_str[j] = '\0';
	return (new_str);
}
