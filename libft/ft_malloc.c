/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:11:17 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 13:51:19 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static void	free_all(t_list *allocs)
{
	t_list	*tmp;

	while (allocs)
	{
		free(allocs->content);
		allocs->content = NULL;
		tmp = allocs;
		allocs = allocs->next;
		free(tmp);
		tmp = NULL;
	}
}

static int	add_node(t_list *allocs, void *pointer)
{
	while (allocs->next)
		allocs = allocs->next;
	allocs->next = malloc(sizeof(t_list));
	if (!allocs->next)
		return (1);
	allocs->next->content = pointer;
	allocs->next->next = NULL;
	return (0);
}

void	*ft_malloc(int size, int free)
{
	static t_list	allocs = {"head", NULL};
	void			*pointer;

	pointer = NULL;
	if (free == 1)
	{
		free_all(allocs.next);
		allocs.next = NULL;
		return (NULL);
	}
	pointer = malloc(size);
	if (!pointer || add_node(&allocs, pointer))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (pointer);
}
