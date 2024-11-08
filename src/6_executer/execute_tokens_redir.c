/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:36:09 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/29 15:51:24 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	token_rdir_in(t_ast_node *node, char **env, int *s_save)
{
	handle_redir(node, env, s_save);
}

void	token_rdir_out(t_ast_node *node, char **env, int *s_save)
{
	handle_redir(node, env, s_save);
}

void	token_rdir_append(t_ast_node *node, char **env, int *s_save)
{
	handle_redir(node, env, s_save);
}
