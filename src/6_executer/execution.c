/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:29:25 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 13:22:03 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_is_echo(char **splits)
{
	int	i;

	i = 0;
	while (splits[i] != NULL)
	{
		if (ft_strcmp(splits[i], "echo") == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**execute_ast(t_ast_node *node, char **env, int *s_save)
{
	int	skip;

	skip = 0;
	if (node == NULL)
		return (env);
	if (node->type == TOKEN_LITERAL)
	{
		env = execute_command(node, env, skip, s_save);
		return (env);
	}
	if (node->type == TOKEN_PIPE)
		token_pipe(node, env, s_save);
	if (node->type == TOKEN_RDIR_IN)
		token_rdir_in(node, env, s_save);
	if (node->type == TOKEN_RDIR_OUT)
		token_rdir_out(node, env, s_save);
	if (node->type == TOKEN_RDIR_APPEND)
		token_rdir_append(node, env, s_save);
	if (node->type == TOKEN_HDOC)
		execute_hdoc(node, env);
	return (env);
}
