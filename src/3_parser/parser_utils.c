/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:22:03 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 11:47:05 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_ast_node	*new_ast_node(t_token_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->heredoc_content = NULL;
	node->delimiters = NULL;
	return (node);
}

static void	free_node_content(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->args)
		free_ast_args(node);
	if (node->heredoc_content)
		free(node->heredoc_content);
	if (node->delimiters)
		free_delimiters_list(node->delimiters);
	node->args = NULL;
	node->heredoc_content = NULL;
	node->delimiters = NULL;
}

void	free_ast_tree(t_ast_node *node)
{
	t_ast_node	*right;
	t_ast_node	*left;

	if (!node)
		return ;
	right = node->right;
	left = node->left;
	node->right = NULL;
	node->left = NULL;
	free_node_content(node);
	free(node);
	if (left)
		free_ast_tree(left);
	if (right)
		free_ast_tree(right);
}

int	get_precedence(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (1);
	if (type >= TOKEN_RDIR_IN && type <= TOKEN_HDOC)
		return (2);
	return (0);
}

int	count_args(t_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == TOKEN_LITERAL && !current->syntax_error)
	{
		arg_count++;
		current = current->next_token;
	}
	return (arg_count);
}
