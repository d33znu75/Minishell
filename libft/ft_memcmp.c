/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:12:53 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:18:32 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n < 1)
		return (0);
	if (*(unsigned char *)s1 - *(unsigned char *)s2)
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	return (ft_memcmp(s1 + 1, s2 + 1, n - 1));
}
