/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:59:19 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:15:58 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*handle_single_quote2(char *str, t_handler *handler)
{
	(handler->i)++;
	while (str[handler->i] && str[handler->i] != '\'')
	{
		handler->new_str[handler->j] = str[handler->i];
		(handler->i)++;
		(handler->j)++;
	}
	handler->arr[handler->x] = ft_strndup(handler->new_str, handler->j);
	(handler->x)++;
	if (str[handler->i] == '\'')
		(handler->i)++;
	return (handler->new_str);
}

static	char	*handle_double_quote2(char *str, t_handler *handler, char **env)
{
	(handler->i)++;
	while (str[handler->i] != '\"')
	{
		handler->new_str[handler->j] = str[handler->i];
		(handler->i)++;
		(handler->j)++;
	}
	handler->arr[handler->x] = \
		expander(ft_strndup(handler->new_str, handler->j), env);
	(handler->x)++;
	if (str[handler->i] == '\"')
		(handler->i)++;
	return (handler->new_str);
}

static	char	*handle_no_quote2(char *str, t_handler *handler, char **env)
{
	while (str[handler->i] != '\'' && str[handler->i] != '\"' \
		&& str[handler->i] != '\0')
	{
		handler->new_str[handler->j] = str[handler->i];
		(handler->i)++;
		(handler->j)++;
	}
	handler->arr[handler->x] = \
		expander(ft_strndup(handler->new_str, handler->j), env);
	(handler->x)++;
	return (handler->new_str);
}

static	char	*handle_loop(char *str, char **env, t_handler *handler)
{
	handler->i = 0;
	handler->j = 0;
	handler->x = 0;
	while (str[handler->i])
	{
		if (str[handler->i] == '\'')
			handler->new_str = handle_single_quote2(str, handler);
		else if (str[handler->i] == '\"')
			handler->new_str = handle_double_quote2(str, handler, env);
		else
			handler->new_str = handle_no_quote2(str, handler, env);
		handler->new_str[0] = '\0';
		handler->j = 0;
	}
	handler->arr[handler->x] = NULL;
	return (handler->new_str);
}

char	*handle_q2(char *str, char **env)
{
	int			len;
	char		*final_str;
	int			k;
	t_handler	handler;

	k = 0;
	len = ft_strlen(str);
	handler.new_str = (char *)ft_malloc(sizeof(char) * (len + 1), 0);
	if (!handler.new_str)
		return (NULL);
	handler.arr = (char **)ft_malloc(sizeof(char *) * (len + 10), 0);
	if (!handler.arr)
		return (NULL);
	final_str = "";
	handler.new_str = handle_loop(str, env, &handler);
	while (handler.arr[k])
	{
		final_str = ft_strjoin(final_str, handler.arr[k]);
		k++;
	}
	return (final_str);
}
