/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 00:55:57 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/29 15:53:44 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_n_option(char *str)
{
	int	i;

	i = 0;
	str = ft_strtrim(str, "\"");
	str = ft_strtrim(str, "\'");
	if (str[i] != '-')
		return (1);
	i++;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo2(char **args, int i, int *s_save)
{
	int	j;

	while (args[i] != NULL)
	{
		if (args[i][0] != '\0')
		{
			j = 0;
			if (*s_save != 0 && i == *s_save)
				j++;
			while (args[i][j] != '\0')
			{
				write(1, &args[i][j], 1);
				j++;
			}
			if (args[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
}

void	ft_echo(char **args, char **env, int *s_save)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (args[i] != NULL && check_n_option(args[i]) == 0)
	{
		newline = 0;
		i++;
	}
	if (newline == 0)
	{
		while (args[i] != NULL && check_n_option(args[i]) == 0)
			i++;
	}
	ft_echo2(args, i, s_save);
	if (newline)
		ft_putstr_fd("\n", 1);
	set_exit_status(env, 0);
}
