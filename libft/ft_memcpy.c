/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:59:07 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:18:35 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst == src || n == 0)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}
