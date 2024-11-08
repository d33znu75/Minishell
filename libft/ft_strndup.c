/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:39:17 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/11 11:19:40 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static size_t	ft_strnlen(char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len])
		len++;
	return (len);
}

char	*ft_strndup(char *src, size_t n)
{
	char	*result;
	size_t	i;
	size_t	size;

	size = ft_strnlen(src, n);
	result = ft_malloc(sizeof(char) * (size + 1), 0);
	i = 0;
	if (result == NULL)
		return (NULL);
	while (i < size)
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
