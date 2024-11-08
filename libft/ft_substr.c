/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:54:05 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:19:49 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	length;
	size_t	index;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	index = 0;
	if (length > len)
		length = len;
	substring = (char *)ft_malloc(sizeof(char) * (length + 1), 0);
	if (!substring)
		return (NULL);
	while (index < length)
	{
		substring[index] = s[start + index];
		index++;
	}
	substring[index] = '\0';
	return (substring);
}
