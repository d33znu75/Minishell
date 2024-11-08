/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:53:53 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:18:44 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

bool	is_special_operator(char *s)
{
	return ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>')
		|| s[0] == '<' || s[0] == '>' || s[0] == '|');
}

bool	is_delimiter(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13)
		|| c == '<' || c == '>' || c == '|');
}

int	word_length(char *s)
{
	int		index;
	bool	inside_quotes;
	char	current_quote;

	1 && (index = 0, inside_quotes = false, current_quote = '\0');
	if (is_special_operator(s))
	{
		if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
			return (2);
		return (1);
	}
	while (s[index] && ((!is_delimiter(s[index])) || inside_quotes))
	{
		if ((s[index] == '\'' || s[index] == '\"')
			&& (!inside_quotes || current_quote == s[index]))
		{
			inside_quotes = !inside_quotes;
			if (inside_quotes)
				current_quote = s[index];
		}
		if (is_special_operator(s + index) && !inside_quotes)
			break ;
		index++;
	}
	return (index);
}

void	*free_memory(char **result, int length)
{
	int	index;

	index = 0;
	while (index < length)
		free(result[index++]);
	free(result);
	return (NULL);
}
