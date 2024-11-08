/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:54:21 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/02 14:16:15 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*expand_env_var1(char *str, char **env, int *i, int j)
{
	char	*var;
	char	*expand;

	expand = "";
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		if (str[*i] == '$')
			break ;
		(*i)++;
		j++;
	}
	if (str[*i] == '?')
	{
		expand = get_env_var(env, "?");
		(*i)++;
	}
	else if (j > 0)
	{
		var = ft_strndup(str + *i - j, j);
		expand = get_env_var(env, var);
		if (expand == NULL)
			expand = "";
	}
	return (expand);
}

char	*handle_dollar_cases(char *str, int *i, char *tmp)
{
	if (str[*i] == '$' && ft_isdigit(str[*i + 1]))
		*i = *i + 2;
	while (str[*i] == '$' && (str[*i + 1] == '$' || str[*i + 1] == '\0'))
	{
		tmp = ft_strjoin_c(tmp, '$');
		(*i)++;
	}
	if (str[*i] == '$' && str[*i + 1] == ' ')
	{
		tmp = ft_strjoin_c(tmp, '$');
		(*i)++;
	}
	return (tmp);
}

char	*expander(char *str, char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	*expand;

	i = 0;
	j = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		tmp = handle_dollar_cases(str, &i, tmp);
		if (str[i] == '$')
		{
			i++;
			expand = expand_env_var1(str, env, &i, j);
			tmp = ft_strjoin(tmp, expand);
		}
		else if (str[i])
		{
			tmp = ft_strjoin_c(tmp, str[i]);
			i++;
		}
	}
	return (tmp);
}
