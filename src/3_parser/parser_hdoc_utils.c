/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hdoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:36:24 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 13:15:46 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*read_pipe_content(int fd)
{
	char	buffer[4096];
	char	*content;
	char	*temp;
	ssize_t	bytes_read;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 4095);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(content, buffer);
		free(content);
		if (!temp)
			return (NULL);
		content = temp;
	}
	if (bytes_read < 0)
	{
		free(content);
		return (NULL);
	}
	return (content);
}

static char	*update_content(char *content, char *line, t_delimiter *delim
			, char **env)
{
	char	*temp;
	char	*expanded_line;

	if (delim->has_quotes == false)
	{
		expanded_line = expander(line, env);
		if (!expanded_line)
			return (NULL);
		temp = join_content(content, expanded_line);
		free(expanded_line);
	}
	else
		temp = join_content(content, line);
	return (temp);
}

char	*process_single_heredoc(t_delimiter *delim, char *content, char **env)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = readline("\033[32m>>\033[0m ");
		if (!line)
			return (content);
		if (ft_strcmp(line, delim->value) == 0)
			return (free(line), content);
		temp = update_content(content, line, delim, env);
		if (!temp)
			return (free(line), free(content), NULL);
		free(line);
		free(content);
		content = temp;
	}
}

char	*read_heredoc_content(t_delimiter *delimiters, char **env)
{
	t_delimiter	*curr;
	char		*content;
	char		*temp;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	curr = delimiters;
	while (curr)
	{
		temp = process_single_heredoc(curr, content, env);
		if (!temp)
			return (NULL);
		content = temp;
		curr = curr->next;
	}
	return (content);
}

int	process_heredoc_tokens(t_ast_node **node, t_token **tokens
		, t_context *context)
{
	context->current = *tokens;
	context->last_valid = context->current;
	while (context->current && context->current->type == TOKEN_HDOC)
	{
		if (!context->current->next_token
			|| context->current->next_token->type != TOKEN_LITERAL)
		{
			set_exit_status(context->env, 258);
			ft_putstr_fd(SYNTAX_ERR, STDERR_FILENO);
			free_ast_tree(*node);
			*tokens = context->last_valid;
			return (1);
		}
		add_delimiter(*node, context->current->next_token->value);
		if (run_heredoc(*node, context->env))
		{
			free_ast_tree(*node);
			*tokens = context->current;
			return (EXIT_FAILURE);
		}
		context->last_valid = context->current->next_token->next_token;
		context->current = context->last_valid;
	}
	*tokens = context->current;
	return (EXIT_SUCCESS);
}
