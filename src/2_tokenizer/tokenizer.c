/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:11:13 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/02 17:56:37 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	check_redirect_sequence(t_token *token)
{
	t_token	*next;

	if (!token)
		return (false);
	next = token->next_token;
	if (!next || next->type != TOKEN_LITERAL)
		return (true);
	return (false);
}

static void	check_syntax_errors(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type >= TOKEN_RDIR_IN && current->type <= TOKEN_HDOC)
		{
			if (check_redirect_sequence(current))
			{
				current->syntax_error = true;
				return ;
			}
		}
		current = current->next_token;
	}
}

t_token	*tokenize_arg(t_token **tokens, char **splitted_args, char *arg)
{
	if (*arg == '|')
		return (new_token(TOKEN_PIPE, arg, tokens, splitted_args));
	else if (*arg == '>' || *arg == '<')
		return (tokenize_redirections(tokens, arg, splitted_args));
	else
		return (new_token(TOKEN_LITERAL, arg, tokens, splitted_args));
}

t_token	*tokenizer(char *cmd_line)
{
	char	**splitted_args;
	char	**arg_iter;
	t_token	*tokens;
	t_token	*new;

	tokens = NULL;
	splitted_args = ft_multi_split(cmd_line);
	if (!splitted_args)
	{
		ft_putstr_fd("Error: tokenizer: split didn't work\n", STDERR_FILENO);
		return (free(cmd_line), cmd_line = NULL, NULL);
	}
	arg_iter = splitted_args;
	while (*arg_iter)
	{
		new = tokenize_arg(&tokens, splitted_args, *arg_iter);
		if (!new)
			return (free(cmd_line), free_tokens(tokens), NULL);
		new->syntax_error = false;
		tokens_list_append(&tokens, new);
		arg_iter++;
	}
	check_syntax_errors(tokens);
	ft_free_list_chars(splitted_args);
	return (tokens);
}
