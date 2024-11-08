/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:44:14 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:18:38 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned const char	*s;
	unsigned char		*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	if (dst == src || n == 0)
		return (dst);
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
		return (dst);
	}
	return (ft_memcpy(dst, src, n));
}
