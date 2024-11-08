/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:52:13 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:18:29 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			index;

	if (n < 1)
		return (NULL);
	index = 0;
	ptr = (unsigned char *)s;
	while (index < n)
	{
		if (ptr[index] == (unsigned char) c)
			return ((void *)(s + index));
		index++;
	}
	return (NULL);
}
