/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:06:30 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:19:22 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	dest_length;
	unsigned int	src_length;
	unsigned int	index;

	src_length = ft_strlen(src);
	if (!dest && !dstsize)
		return (src_length);
	dest_length = ft_strlen(dest);
	index = 0;
	if (dest_length >= dstsize)
		return (src_length + dstsize);
	while (src[index] && dest_length + index < dstsize - 1)
	{
		dest[dest_length + index] = src[index];
		index++;
	}
	dest[dest_length + index] = '\0';
	return (src_length + dest_length);
}
