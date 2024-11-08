/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:55:00 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:19:20 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	total_size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)ft_malloc(sizeof(char) * total_size, 0);
	if (!result)
		return (NULL);
	*result = '\0';
	ft_strlcat(result, s1, total_size);
	ft_strlcat(result, s2, total_size);
	return (result);
}
