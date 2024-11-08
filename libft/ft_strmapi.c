/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:12:19 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:19:29 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		index;
	unsigned int		length;
	char				*result;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	index = 0;
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	while (index < length)
	{
		result[index] = (*f)(index, s[index]);
		index++;
	}
	result[index] = '\0';
	return (result);
}
