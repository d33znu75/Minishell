/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:36:55 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:19:07 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	count_words(char *s)
{
	int		counter;
	bool	in_q;
	char	cur_q;

	1 && (counter = 0, in_q = false, cur_q = '\0');
	while (*s)
	{
		while (*s && (*s == ' ' || (*s >= 9 && *s <= 13)) && !in_q)
			s++;
		if (*s && (!(*s == ' ' || (*s >= 9 && *s <= 13)) || in_q))
		{
			while (*s && (!(*s == ' ' || (*s >= 9 && *s <= 13)) || in_q))
			{
				if ((*s == '\'' || *s == '\"') && (!in_q || cur_q == *s))
				{
					in_q = !in_q;
					if (in_q)
						cur_q = *s;
				}
				s++;
			}
			counter++;
		}
	}
	return (counter);
}

static int	word_length_static(char *s)
{
	int		index;
	bool	in_q;
	char	cur_q;

	index = 0;
	in_q = false;
	cur_q = '\0';
	while (s[index] && (!((s[index] == ' ' \
		|| (s[index] >= 9 && s[index] <= 13)) && !in_q)))
	{
		if ((s[index] == '\'' || s[index] == '\"') \
			&& (!in_q || cur_q == s[index]))
		{
			in_q = !in_q;
			if (in_q)
				cur_q = s[index];
		}
		index++;
	}
	return (index);
}

static void	*free_memory_static(char **result, int length)
{
	int	index;

	index = 0;
	while (index < length)
		free(result[index++]);
	free(result);
	return (NULL);
}

char	**ft_split(char *s)
{
	char	**result;
	int		index;
	int		words_count;
	int		length_of_word;

	if (s == NULL)
		return (NULL);
	words_count = count_words(s);
	result = (char **)ft_malloc(sizeof(char *) * (words_count + 1), 0);
	if (!result)
		return (NULL);
	index = 0;
	while (index < words_count)
	{
		while (*s && (*s == ' ' || (*s >= 9 && *s <= 13)))
			s++;
		length_of_word = word_length_static(s);
		result[index] = ft_substr(s, 0, length_of_word);
		if (!result[index])
			return (free_memory_static(result, index), NULL);
		index++;
		s += length_of_word;
	}
	result[index] = NULL;
	return (result);
}
