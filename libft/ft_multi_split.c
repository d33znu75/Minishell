/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:54:14 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/30 16:36:31 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	handle_special_operator(char **s)
{
	if ((**s == '<' && *(*s + 1) == '<') || (**s == '>' && *(*s + 1) == '>'))
		*s += 2;
	else
		(*s)++;
	return (1);
}

static int	handle_regular_chars(char **s)
{
	bool	inside_quotes;
	char	current_quote;

	inside_quotes = false;
	current_quote = '\0';
	while (**s && (!is_delimiter(**s) || inside_quotes))
	{
		if ((**s == '\'' || **s == '\"')
			&& (!inside_quotes || current_quote == **s))
		{
			inside_quotes = !inside_quotes;
			if (inside_quotes)
				current_quote = **s;
		}
		if (is_special_operator(*s) && !inside_quotes)
			break ;
		(*s)++;
	}
	return (1);
}

static int	count_words(char *s)
{
	int		counter;
	bool	inside_quotes;

	counter = 0;
	inside_quotes = false;
	while (*s)
	{
		while (*s && is_delimiter(*s) && !inside_quotes)
		{
			if (is_special_operator(s))
				break ;
			s++;
		}
		if (*s)
		{
			if (is_special_operator(s))
				counter += handle_special_operator(&s);
			else
				counter += handle_regular_chars(&s);
		}
	}
	return (counter);
}

char	**ft_multi_split(char *s)
{
	char	**result;
	int		words_count;
	int		index;
	int		len_word;

	if (!s)
		return (NULL);
	words_count = count_words(s);
	result = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!result)
		return (NULL);
	index = 0;
	while (index < words_count)
	{
		while (*s && is_delimiter(*s) && !is_special_operator(s))
			s++;
		len_word = word_length(s);
		result[index] = ft_strndup(s, len_word);
		if (!result[index])
			return (free_memory(result, index));
		index++;
		s += len_word;
	}
	result[index] = NULL;
	return (result);
}
