/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:23:12 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/22 14:11:16 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next_token = NULL;
	token->prev_token = NULL;
	return (token);
}

t_token	*new_token(t_token_type type, char *value, t_token **tokens,
			char **splitted_args)
{
	t_token	*new_token;

	new_token = create_token(type, value);
	if (!new_token)
	{
		free_tokens(*tokens);
		ft_free_list_chars(splitted_args);
		ft_putstr_fd(MALLOC_FAILED, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (new_token);
}

void	tokens_list_append(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next_token)
			last = last->next_token;
		last->next_token = new_token;
		new_token->prev_token = last;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*last;
	t_token	*temp;

	if (!tokens)
		return ;
	last = tokens;
	while (last->next_token)
		last = last->next_token;
	while (last)
	{
		temp = last;
		last = last->prev_token;
		free(temp->value);
		free(temp);
	}
}

t_token	*tokenize_redirections(t_token **tokens, char *token,
			char **splitted_args)
{
	if (*token == '<')
	{
		if (*(token + 1) && *(token + 1) == '<')
			return (new_token(TOKEN_HDOC, "<<", tokens, splitted_args));
		else
			return (new_token(TOKEN_RDIR_IN, "<", tokens, splitted_args));
	}
	else if (*token == '>')
	{
		if (*(token + 1) && *(token + 1) == '>')
			return (new_token(TOKEN_RDIR_APPEND, ">>", tokens, splitted_args));
		else
			return (new_token(TOKEN_RDIR_OUT, ">", tokens, splitted_args));
	}
	return (NULL);
}
