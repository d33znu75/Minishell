/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:21:58 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 11:47:05 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	f2n(t_ast_node *node1, t_ast_node *node2)
{
	free_ast_tree(node1);
	free_ast_tree(node2);
}

t_ast_node	*handle_redirect_token(t_ast_node **root, t_token **tokens,
				char **env)
{
	t_ast_node	*rdir_node;

	if (!tokens || !*tokens || (*tokens)->syntax_error)
		return (print_and_exit(env), free_ast_tree(*root), NULL);
	if ((*tokens)->type == TOKEN_HDOC)
	{
		rdir_node = handle_heredocs(tokens, env);
		if (!rdir_node)
			return (free_ast_tree(*root), NULL);
	}
	else
	{
		rdir_node = new_ast_node((*tokens)->type);
		if (!rdir_node)
			return (free_ast_tree(*root), NULL);
		*tokens = (*tokens)->next_token;
		if (!*tokens || (*tokens)->syntax_error)
			return (print_and_exit(env), f2n(*root, rdir_node), NULL);
		rdir_node->right = create_file_node(tokens, env);
		if (!rdir_node->right)
			return (free_ast_tree(*root), free_ast_tree(rdir_node), NULL);
	}
	if (*root)
		rdir_node->left = *root;
	return (*root = rdir_node, *root);
}

t_ast_node	*handle_redirection(t_ast_node *left, t_token **tokens, char **env)
{
	t_ast_node	*operator_node;

	if (!tokens || !*tokens || (*tokens)->syntax_error)
		return (print_and_exit(env), free_ast_tree(left), NULL);
	if ((*tokens)->type == TOKEN_HDOC)
	{
		operator_node = handle_heredocs(tokens, env);
		if (!operator_node)
			return (free_ast_tree(left), NULL);
	}
	else
	{
		operator_node = new_ast_node((*tokens)->type);
		if (!operator_node)
			return (free_ast_tree(left), NULL);
		*tokens = (*tokens)->next_token;
		if (!*tokens || (*tokens)->syntax_error)
			return (print_and_exit(env), free_ast_tree(left)
				, free_ast_tree(operator_node), NULL);
		operator_node->right = create_file_node(tokens, env);
		if (!operator_node->right)
			return (free_ast_tree(left), free_ast_tree(operator_node), NULL);
	}
	operator_node->left = left;
	return (operator_node);
}

t_ast_node	*create_file_node(t_token **tokens, char **env)
{
	t_ast_node	*node;

	if (!tokens || !*tokens || (*tokens)->syntax_error)
		return (print_and_exit(env), NULL);
	node = new_ast_node(TOKEN_LITERAL);
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
		return (free_ast_tree(node), NULL);
	node->args[0] = ft_strdup((*tokens)->value);
	if (!node->args[0])
		return (free_ast_tree(node), NULL);
	node->args[1] = NULL;
	*tokens = (*tokens)->next_token;
	return (node);
}

t_ast_node	*handle_pipes(t_ast_node *left, t_token **tokens, int precedence,
				char **env)
{
	t_ast_node	*operator_node;

	if (!tokens || !*tokens || (*tokens)->syntax_error)
		return (print_and_exit(env), free_ast_tree(left), NULL);
	operator_node = new_ast_node((*tokens)->type);
	if (!operator_node)
		return (free_ast_tree(left), NULL);
	operator_node->left = left;
	*tokens = (*tokens)->next_token;
	if (!*tokens || (*tokens)->syntax_error)
	{
		operator_node->left = NULL;
		free_ast_tree(operator_node);
		return (print_and_exit(env), free_ast_tree(left), NULL);
	}
	operator_node->right = parse_expression(tokens, precedence, env);
	if (!operator_node->right)
	{
		operator_node->left = NULL;
		free_ast_tree(operator_node);
		return (free_ast_tree(left), NULL);
	}
	return (operator_node);
}
