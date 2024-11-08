/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:22:07 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 11:47:05 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_ast_node	*parse_commands(t_token **tokens, char **env)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->syntax_error)
		return (print_and_exit(env), NULL);
	return (parse_command_with_redirects(tokens, env));
}

t_ast_node	*parse_operators(t_ast_node *left, t_token **tokens, \
	int precedence, char **env)
{
	t_ast_node	*node;

	if (!left || !tokens || !*tokens)
		return (NULL);
	if ((*tokens)->syntax_error)
		return (print_and_exit(env), NULL);
	if ((*tokens)->type >= TOKEN_RDIR_IN && (*tokens)->type <= TOKEN_HDOC)
	{
		node = handle_redirection(left, tokens, env);
		if (!node || !append_literal_args(left, tokens))
			return (print_and_exit(env), free_ast_tree(node), NULL);
		return (node);
	}
	else
		return (handle_pipes(left, tokens, precedence, env));
}

t_ast_node	*parse_expression(t_token **tokens, int precedence, char **env)
{
	t_ast_node	*left;

	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->syntax_error)
		return (print_and_exit(env), NULL);
	left = parse_commands(tokens, env);
	if (!left)
		return (NULL);
	while (*tokens && get_precedence((*tokens)->type) > precedence)
	{
		if ((*tokens)->syntax_error)
		{
			free_ast_tree(left);
			return (print_and_exit(env), NULL);
		}
		left = parse_operators(left, tokens, \
				get_precedence((*tokens)->type), env);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast_node	*parser(t_token **tokens, char **env)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->syntax_error)
		return (print_and_exit(env), NULL);
	return (parse_expression(tokens, 0, env));
}
