/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:21:52 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/23 09:00:46 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_ast_args(t_ast_node *node)
{
	int	i;

	i = 0;
	if (node && node->type == TOKEN_LITERAL && node->args)
	{
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
}

int	append_arg(t_ast_node *node, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (node->args && node->args[i])
		i++;
	new_args = ft_realloc_args(node->args, i, i + 1);
	if (!new_args)
		return (0);
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
		return (free(new_args), 0);
	node->args = new_args;
	return (1);
}

char	**ft_realloc_args(char **args, int current_size, int new_size)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (new_size + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < current_size)
	{
		new_args[i] = args[i];
		i++;
	}
	while (i <= new_size)
		new_args[i++] = NULL;
	free(args);
	return (new_args);
}

int	append_literal_args(t_ast_node *left, t_token **tokens)
{
	int		i;
	char	**new_args;

	while (*tokens && (*tokens)->type == TOKEN_LITERAL)
	{
		if ((*tokens)->syntax_error)
			return (0);
		i = 0;
		while (left->args[i])
			i++;
		new_args = ft_realloc_args(left->args, i, i + 1);
		if (!new_args)
			return (0);
		left->args = new_args;
		left->args[i] = ft_strdup((*tokens)->value);
		if (!left->args[i])
			return (0);
		*tokens = (*tokens)->next_token;
	}
	return (1);
}
