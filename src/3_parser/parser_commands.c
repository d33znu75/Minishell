/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:21:43 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 11:47:05 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	link_cmd_to_leftmost(t_ast_node *root, t_ast_node *cmd_node)
{
	t_ast_node	*tmp;

	tmp = root;
	while (tmp->left)
		tmp = tmp->left;
	tmp->left = cmd_node;
}

t_ast_node	*handle_literal_token(t_ast_node **root, t_ast_node **cmd_node,
				t_token **tokens, char **env)
{
	if ((*tokens)->syntax_error)
	{
		set_exit_status(env, 258);
		return (ft_putstr_fd(SYNTAX_ERR, 2), free_ast_tree(*root), NULL);
	}
	if (!*cmd_node)
	{
		*cmd_node = create_command_node(tokens, env);
		if (!*cmd_node)
			return (NULL);
		if (*root)
			link_cmd_to_leftmost(*root, *cmd_node);
		else
			*root = *cmd_node;
	}
	else
	{
		if (!append_arg(*cmd_node, (*tokens)->value))
			return (NULL);
		*tokens = (*tokens)->next_token;
	}
	return (*root);
}

t_ast_node	*parse_command_with_redirects(t_token **tokens, char **env)
{
	t_ast_node	*root;
	t_ast_node	*cmd_node;

	root = NULL;
	cmd_node = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->syntax_error)
		{
			set_exit_status(env, 258);
			return (ft_putstr_fd(SYNTAX_ERR, 2), free_ast_tree(root), NULL);
		}
		if ((*tokens)->type == TOKEN_LITERAL)
			root = handle_literal_token(&root, &cmd_node, tokens, env);
		else if ((*tokens)->type >= TOKEN_RDIR_IN
			&& (*tokens)->type <= TOKEN_HDOC)
			root = handle_redirect_token(&root, tokens, env);
		if (!root)
			return (NULL);
	}
	return (root);
}

t_ast_node	*create_command_node(t_token **tokens, char **env)
{
	t_ast_node	*node;

	if ((*tokens)->syntax_error)
	{
		set_exit_status(env, 258);
		return (ft_putstr_fd(SYNTAX_ERR, 2), NULL);
	}
	node = new_ast_node(TOKEN_LITERAL);
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
		return (free(node), NULL);
	node->args[0] = ft_strdup((*tokens)->value);
	if (!node->args[0])
		return (free(node->args), free(node), NULL);
	node->args[1] = NULL;
	*tokens = (*tokens)->next_token;
	return (node);
}
