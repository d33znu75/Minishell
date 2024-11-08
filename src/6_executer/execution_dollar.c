/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:00:29 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 18:01:24 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_dollar_handler	*init_dollar_handler(char **splits, char **env, int len)
{
	t_dollar_handler	*st;

	st = (t_dollar_handler *)ft_malloc(sizeof(t_dollar_handler), 0);
	st->len = len;
	st->x = 0;
	st->z = 0;
	st->z1 = 0;
	st->splits = splits;
	st->env = env;
	st->tmp_splits = (char **)ft_malloc(sizeof(char *) * len, 0);
	st->tmp_sp2 = NULL;
	return (st);
}

void	realloc_splits(t_dollar_handler *st)
{
	if (st->x >= st->len)
	{
		st->len *= 2;
		st->tmp_splits = realloc(st->tmp_splits, sizeof(char *) * st->len);
	}
}

void	handle_splits_with_dollar(t_dollar_handler *st)
{
	while (st->tmp_sp2 && st->z1 && st->tmp_sp2[st->z1] != NULL)
	{
		realloc_splits(st);
		st->tmp_splits[st->x] = ft_strdup(st->tmp_sp2[st->z1]);
		st->x++;
		st->z1++;
	}
	st->z1 = 0;
}

char	**split_with_dollar(t_dollar_handler *st)
{
	int	hs;

	hs = 0;
	if (has_quotes(st->splits[st->z]) == 1 && st->splits[st->z][0] == '$')
		st->tmp_sp2 = ft_split_q(expander(st->splits[st->z], st->env), ' ');
	else
	{
		hs = has_quotes(st->splits[st->z]);
		st->tmp_sp2 = ft_split2(handle_q2(st->splits[st->z], st->env), ' ');
		st->tmp_sp2 = realloc(st->tmp_sp2, sizeof(char *) * 2);
		if (st->tmp_sp2[0] == NULL && hs == 1)
		{
			st->tmp_sp2[0] = ft_strdup("");
			st->tmp_sp2[1] = NULL;
		}
	}
	return (st->tmp_sp2);
}

char	**handle_dollar(char **splits, char **env, int len)
{
	t_dollar_handler	*st;

	st = init_dollar_handler(splits, env, len);
	if (!st->tmp_splits)
		return (NULL);
	while (st->splits[st->z] != NULL)
	{
		st->splits[st->z] = handle_q2(st->splits[st->z], st->env);
		realloc_splits(st);
		if (has_dollar(st->splits[st->z]) == 1 && ft_is_echo(st->splits) == 0)
			st->tmp_sp2 = split_with_dollar(st);
		else
		{
			st->tmp_splits[st->x] = handle_q2(st->splits[st->z], st->env);
			st->x++;
			st->z++;
			continue ;
		}
		handle_splits_with_dollar(st);
		st->z++;
	}
	realloc_splits(st);
	return (st->tmp_splits[st->x] = NULL, st->tmp_splits);
}
