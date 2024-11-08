/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hdoc_delimiter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:35:06 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 12:10:03 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	which_quote(char c, bool *has_quotes)
{
	if (c == '\'' || c == '"')
		*has_quotes = true;
	if (c == '\'')
		return (1);
	else
		return (2);
}

static char	*process_delimiter_value(char *value, bool *has_quotes)
{
	char	*trimmed;
	size_t	len;
	int		quote_type;
	int		i;
	int		j;

	len = ft_strlen(value);
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	1 && (i = 0, j = 0, quote_type = 0, *has_quotes = false);
	while (value[i])
	{
		if (!quote_type && (value[i] == '\'' || value[i] == '"'))
			quote_type = which_quote(value[i], has_quotes);
		else if ((quote_type == 1 && value[i] == '\'')
			|| (quote_type == 2 && value[i] == '"'))
			quote_type = 0;
		else
			trimmed[j++] = value[i];
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

t_delimiter	*create_delimiter(char *value)
{
	t_delimiter	*new;
	char		*trimmed_value;
	char		*final_value;

	new = malloc(sizeof(t_delimiter));
	if (!new)
		return (NULL);
	trimmed_value = process_delimiter_value(value, &new->has_quotes);
	if (!trimmed_value)
		return (free(new), NULL);
	final_value = ft_strdup(trimmed_value);
	free(trimmed_value);
	if (!final_value)
		return (free(new), NULL);
	new->value = final_value;
	new->next = NULL;
	return (new);
}

void	add_delimiter(t_ast_node *node, char *value)
{
	t_delimiter	*new;
	t_delimiter	*current;

	new = create_delimiter(value);
	if (!new)
		return ;
	if (!node->delimiters)
		node->delimiters = new;
	else
	{
		current = node->delimiters;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	free_delimiters_list(t_delimiter *delimiters)
{
	t_delimiter	*current;
	t_delimiter	*next;

	current = delimiters;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
