/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:28:19 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 17:43:00 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_get_splits	*init_get_splits(t_ast_node *node, char **env)
{
	t_get_splits	*get_splits;

	get_splits = (t_get_splits *)ft_malloc(sizeof(t_get_splits), 0);
	if (!get_splits)
		return (NULL);
	get_splits->splits = (char **)ft_malloc(sizeof(char *) * ARG_MAX, 0);
	if (!get_splits->splits)
		return (NULL);
	get_splits->get_splits = NULL;
	get_splits->z = 0;
	get_splits->b = 0;
	get_splits->d = 0;
	get_splits->node = node;
	get_splits->env = env;
	return (get_splits);
}

static void	handle_env_var_exists(t_get_splits *get_splits)
{
	get_splits->get_splits = \
		ft_split2(get_env_var(get_splits->env, \
			get_splits->node->args[get_splits->d] + 1), ' ');
	while (get_splits->get_splits && \
			get_splits->get_splits[get_splits->b] != NULL)
	{
		get_splits->splits[get_splits->z] = \
			ft_strdup(get_splits->get_splits[get_splits->b]);
		get_splits->b++;
		get_splits->z++;
	}
	get_splits->b = 0;
	get_splits->d++;
}

static void	handle_env_var_not_exists(t_get_splits *get_splits)
{
	get_splits->splits[get_splits->z] = get_splits->node->args[get_splits->d];
	get_splits->z++;
	get_splits->d++;
}

static char	**ret_sp(int handler, char **tmp_splits, char **tmp)
{
	int		i;
	int		k;
	char	**tmp_splits2;

	i = 0;
	k = 0;
	tmp_splits2 = (char **)ft_malloc(sizeof(char *) * ARG_MAX, 0);
	if (!tmp_splits2)
		return (NULL);
	while (tmp_splits[i] && handler != -1)
	{
		if (handler == i)
		{
			tmp = ft_split2(tmp_splits[i], ' ');
			while (*tmp)
				tmp_splits2[k++] = ft_strdup(*tmp++);
		}
		else
			tmp_splits2[k++] = ft_strdup(tmp_splits[i]);
		i++;
	}
	return (tmp_splits2[k] = NULL, tmp_splits);
}

char	**get_splits(t_ast_node *node, char **env, int handler)
{
	t_get_splits	*get_splits;
	char			**tmp_splits;
	char			**tmp;

	tmp = NULL;
	get_splits = init_get_splits(node, env);
	if (!get_splits->splits)
		return (NULL);
	while (get_splits->node->args[get_splits->d] != NULL)
	{
		if (ft_strncmp(get_splits->node->args[get_splits->d], "$", 1) == 0 \
			&& check_env_var(get_splits->env, \
				get_splits->node->args[get_splits->d] + 1) == 1)
			handle_env_var_exists(get_splits);
		else if (ft_strncmp(get_splits->node->args[get_splits->d], "$", 1) == 0 \
			&& check_env_var(get_splits->env, \
				get_splits->node->args[get_splits->d] + 1) == 0)
			handle_env_var_not_exists(get_splits);
		else
			handle_env_var_not_exists(get_splits);
	}
	get_splits->splits[get_splits->z] = NULL;
	tmp_splits = handle_dollar(get_splits->splits, \
								get_splits->env, get_splits->z);
	return (ret_sp(handler, tmp_splits, tmp));
}
