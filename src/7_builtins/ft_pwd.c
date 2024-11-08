/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:54:54 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/10/03 01:19:54 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(char **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		set_exit_status(env, 0);
	}
	else
	{
		set_exit_status(env, 1);
		ft_putstr_fd("minibash: ", 2);
		perror(NULL);
	}
	return ;
}

char	*ft_pwd_str(char **env)
{
	char	cwd[PATH_MAX];
	char	*str;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		str = ft_strdup(cwd);
		return (str);
	}
	else
	{
		set_exit_status(env, 1);
		ft_putstr_fd("minibash: ", 2);
		perror(NULL);
	}
	return (NULL);
}
