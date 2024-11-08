/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:05 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/11 11:19:05 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

t_split	*init_split(const char *str)
{
	t_split	*split;

	split = (t_split *)ft_malloc(sizeof(t_split), 0);
	if (!split)
		return (NULL);
	split->count = 0;
	split->len = 0;
	split->i = 0;
	split->in_single_quote = 0;
	split->in_double_quote = 0;
	split->result = \
		(char **)ft_malloc(sizeof(char *) * (ft_strlen(str) + 1), 0);
	split->current = \
		(char *)ft_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	if (!split->result || !split->current)
		return (NULL);
	return (split);
}

void	handle_quotes(t_split *split, const char *str, char delimiter)
{
	if (str[split->i] == '\'' && !split->in_double_quote)
		split->in_single_quote = !split->in_single_quote;
	else if (str[split->i] == '\"' && !split->in_single_quote)
		split->in_double_quote = !split->in_double_quote;
	else if (str[split->i] == delimiter \
		&& !split->in_single_quote && !split->in_double_quote)
	{
		split->current[split->len] = '\0';
		split->result[split->count] = ft_strdup(split->current);
		split->count++;
		split->len = 0;
	}
	else
		split->current[split->len++] = str[split->i];
}

char	**ft_split_q(const char *str, char delimiter)
{
	t_split	*split;

	split = init_split(str);
	if (!split)
		return (NULL);
	while (str[split->i] != '\0')
	{
		handle_quotes(split, str, delimiter);
		split->i++;
	}
	if (split->len > 0)
	{
		split->current[split->len] = '\0';
		split->result[split->count] = ft_strdup(split->current);
		split->count++;
	}
	split->result[split->count] = NULL;
	return (split->result);
}

// char **ft_split_q(const char *str, char delimiter)
// {
// 	char    **result;
// 	char    *current;
// 	size_t  count;
// 	size_t  len;
// 	size_t  i;
// 	int     in_single_quote;
// 	int     in_double_quote;

// 	count = 0;
// 	len = 0;
// 	i = 0;
// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	result = (char **)ft_malloc(sizeof(char *) * (ft_strlen(str) + 1), 0);
// 	if (!result)
// 		return NULL;
// 	current = (char *)ft_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
// 	if (!current)
// 		return NULL;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'' && !in_double_quote)
// 			in_single_quote = !in_single_quote;
// 		else if (str[i] == '\"' && !in_single_quote)
// 			in_double_quote = !in_double_quote;
// 		else if (str[i] == delimiter && !in_single_quote && !in_double_quote)
// 		{
// 			current[len] = '\0';
// 			result[count] = ft_strdup(current);
// 			count++;
// 			len = 0;
// 		}
// 		else
// 			current[len++] = str[i];
// 		i++;
// 	}
// 	if (len > 0)
// 	{
// 		current[len] = '\0';
// 		result[count] = ft_strdup(current);
// 		count++;
// 	}
// 	result[count] = NULL;
// 	return (result);
// }