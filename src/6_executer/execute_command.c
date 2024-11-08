/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:06:57 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 13:34:56 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	int	get_skip(char **tmp_splits, char **args, char **env)
{
	int	skip;
	int	j;

	skip = 0;
	j = 0;
	if (ft_is_echo(tmp_splits) == 1)
	{
		while (args[j] != NULL)
		{
			if (ft_strncmp(args[j], "echo", 4) == 0)
				break ;
			if (ft_strncmp(expander(args[j], env), "", 1) == 0)
				skip++;
			j++;
		}
	}
	return (skip);
}

int	has_quotes(char *str)
{
	int	i;
	int	single_qoutes;
	int	double_qoutes;

	i = 0;
	single_qoutes = 0;
	double_qoutes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_qoutes++;
		if (str[i] == '\"')
			double_qoutes++;
		i++;
	}
	if (single_qoutes > 0 || double_qoutes > 0)
		return (1);
	return (0);
}

int	dollar_with_quotes(t_ast_node *node)
{
	int	i;

	i = 0;
	while (node->args[i])
	{
		if (node->args[i][0] == '$' && has_quotes(node->args[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	skip_dollar_quote(t_ast_node *node, int *s_save)
{
	int	i;

	i = 0;
	while (node->args[i])
	{
		if (ft_strncmp(node->args[i], "$", 1) == 0 \
			&& (node->args[i][1] == '\'' || node->args[i][1] == '\"'))
			*s_save = i;
		i++;
	}
}

char	**execute_command(t_ast_node *node, char **env, int skip, int *s_save)
{
	char	**tmp_splits;
	int		handler;

	skip_dollar_quote(node, s_save);
	handler = dollar_with_quotes(node);
	tmp_splits = get_splits(node, env, handler);
	skip = get_skip(tmp_splits, node->args, env);
	if (tmp_splits[skip] == NULL)
		return (env);
	if (ft_strcmp(tmp_splits[skip], "exit") == 0)
		return (ft_exit(&tmp_splits[skip], env), env);
	else if (ft_strcmp(tmp_splits[skip], "cd") == 0)
		return (env = ft_cd(&tmp_splits[skip], env), env);
	else if (ft_strcasecmp(tmp_splits[skip], "echo") == 0)
		return (ft_echo(&tmp_splits[skip], env, s_save), env);
	else if (ft_strcasecmp(tmp_splits[skip], "pwd") == 0)
		return (ft_pwd(env), env);
	else if (ft_strcmp(tmp_splits[skip], "export") == 0)
		return (env = ft_export(&tmp_splits[skip], env), env);
	else if (ft_strcmp(tmp_splits[skip], "unset") == 0)
		return (env = ft_unset(&tmp_splits[skip], env), env);
	else if (ft_strcasecmp(tmp_splits[skip], "env") == 0)
		return (ft_env(env), env);
	else
		return (env = execute_command_in_bin(&tmp_splits[skip], env), env);
}
