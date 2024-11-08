/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hdoc_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:01:25 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 11:47:05 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*join_content(char *content, char *line)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(content, line);
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, "\n");
	free(temp1);
	if (!temp2)
		return (NULL);
	return (temp2);
}

t_context	create_context(t_token *current, t_token *last_valid, char **env)
{
	t_context	context;

	context.current = current;
	context.last_valid = last_valid;
	context.env = env;
	return (context);
}

t_ast_node	*init_heredoc_node(void)
{
	t_ast_node	*node;

	node = new_ast_node(TOKEN_HDOC);
	if (!node)
		return (NULL);
	node->heredoc_content = ft_strdup("");
	if (!node->heredoc_content)
	{
		free_ast_tree(node);
		return (NULL);
	}
	return (node);
}

void	print_and_exit(char **env)
{
	ft_putstr_fd(SYNTAX_ERR, STDOUT_FILENO);
	set_exit_status(env, 258);
}
