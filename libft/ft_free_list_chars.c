/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:42:14 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/11 11:18:06 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	ft_free_list_chars(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
