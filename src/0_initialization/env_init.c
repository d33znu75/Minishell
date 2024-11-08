/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:44:46 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 17:13:28 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**env_init_null(void)
{
	char	**env;
	char	*path;
	char	*cwd;

	env = (char **)ft_malloc(sizeof(char *) * 7, 0);
	if (!env)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_err("minibash: ", "getcwd", "error path\n", STDERR_FILENO);
		return (NULL);
	}
	path = ft_strjoin("PWD=", cwd);
	env[0] = ft_strdup("SHLVL=1");
	env[1] = ft_strdup("_=/usr/bin/env");
	env[2] = ft_strdup(path);
	env[3] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[4] = ft_strdup("OLDPWD");
	env[5] = ft_strdup("?=0");
	env[6] = NULL;
	free(path);
	free(cwd);
	return (env);
}

static char	**copy_env(char **copy, char **environ)
{
	int	m;
	int	n;

	m = 0;
	n = 0;
	while (environ[m])
	{
		if (ft_strchr(environ[m], '=') != NULL \
			&& ft_strncmp(environ[m], "OLDPWD", 6) != 0)
		{
			copy[n] = ft_strdup(environ[m]);
			if (copy[n] == NULL)
				return (NULL);
			n++;
		}
		m++;
	}
	return (copy[n] = NULL, copy);
}

char	**env_init(char **environ)
{
	int		i;
	char	**copy;
	char	*home;
	char	*tilde;
	char	*temp[2];

	i = 0;
	while (environ[i] != NULL)
		i++;
	copy = ft_malloc((i + 1) * sizeof(char *), 0);
	if (copy == NULL)
		return (NULL);
	copy = copy_env(copy, environ);
	home = get_env_var(copy, "HOME");
	tilde = ft_strjoin("~=", home);
	temp[0] = "OLDPWD";
	temp[1] = NULL;
	copy = ft_unset(temp, copy);
	copy = add_env_var(copy, tilde);
	copy = add_env_var(copy, "OLDPWD");
	return (copy);
}
