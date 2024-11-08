/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:50:59 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/11 11:19:09 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	count_word(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	ft_free(char **ret, int i)
{
	i = i - 1;
	while (i >= 0)
	{
		free(ret[i]);
		i--;
	}
	free(ret);
}

static char	**s_plit(char const *s, char c, char **ret, const char *start)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			ret[i] = ft_substr(start, 0, s - start);
			if (ret[i] == NULL)
			{
				ft_free(ret, i);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**ft_split2(char const *s, char c)
{
	int			count;
	char		**ret;
	const char	*start;

	if (s == NULL)
		return (NULL);
	count = count_word(s, c);
	ret = ft_malloc((count + 1) * sizeof(char *), 0);
	if (ret == NULL)
		return (NULL);
	return (s_plit(s, c, ret, start));
}
