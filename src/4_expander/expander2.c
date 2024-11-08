/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:52:41 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:16:29 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strjoin_c(char *s1, char c)
{
	size_t	len;
	char	*ret;
	char	s2[2];

	if (s1 == NULL)
		return (NULL);
	s2[0] = c;
	s2[1] = '\0';
	len = ft_strlen(s1) + 1;
	ret = ft_malloc(len + 1, 0);
	if (ret == NULL)
		return (NULL);
	ft_strcpy(ret, s1);
	ft_strcat(ret, s2);
	return (ret);
}

static char	*expand_env_var2(char *str, char **env, int *i)
{
	int		j;
	char	*var;
	char	*expand;

	j = 0;
	while (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '?')
	{
		if (str[*i] == '$')
			break ;
		(*i)++;
		j++;
	}
	var = ft_strndup(str + *i - j, j);
	expand = get_env_var(env, var);
	return (expand);
}

char	*expander2(char *str, char **env)
{
	int		i;
	char	*expand;
	char	*tmp;

	i = 0;
	tmp = "";
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			expand = expand_env_var2(str, env, &i);
			tmp = ft_strjoin(tmp, expand);
		}
		else
		{
			tmp = ft_strjoin_c(tmp, str[i]);
			i++;
		}
	}
	return (tmp);
}
