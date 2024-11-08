/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:23:51 by abzaiz            #+#    #+#             */
/*   Updated: 2024/11/04 17:36:47 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	result;

	result = 0;
	if (!s)
		return (0);
	while (s[result])
		result++;
	return (result);
}
