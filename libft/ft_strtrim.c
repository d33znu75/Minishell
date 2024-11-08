/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:12:05 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/16 16:47:29 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (s1 && !set)
		return ((char *)s1);
	result = NULL;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (end > start && s1[end - 1] && ft_strchr(set, s1[end - 1]))
			end--;
		result = (char *)ft_malloc(sizeof(char) * (end - start + 1), 0);
		if (result)
			ft_strlcpy(result, s1 + start, end - start + 1);
	}
	return (result);
}
