/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:45:05 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 15:08:31 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static	char	**main2(char **env, char *input, int *s_save)
{
	t_ast_node		*ast;
	t_ast_node		*ast_ptr;
	t_token			*tokens;
	t_token			*tokens_ptr;
	int				syntax;

	ast = NULL;
	syntax = has_syntax_error(input, env);
	if (syntax == 1)
		return (env);
	tokens = tokenizer(input);
	tokens_ptr = tokens;
	if (tokens && syntax == 0)
		ast = parser(&tokens, env);
	ast_ptr = ast;
	free_tokens(tokens_ptr);
	env = main_g_exit(env);
	add_history(input);
	if (ast && syntax == 0)
		env = execute_ast(ast, env, s_save);
	if (ast_ptr)
		free_ast_tree(ast_ptr);
	return (env);
}

void	process_input(char **env, struct termios term, int syntax, int *s_save)
{
	t_ast_node		*ast;
	t_token			*tokens;
	char			*input;

	while (69)
	{
		initialize_signals();
		1 && (syntax = 0, input = NULL);
		input = readline("minibash$ ");
		if (input == NULL)
			ctrl_d_handler(env);
		else
		{
			if (*input == '\0')
			{
				free(input);
				input = NULL;
				continue ;
			}
			1 && (ast = NULL, tokens = NULL);
			env = main2(env, input, s_save);
			tcsetattr(0, TCSANOW, &term);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **environ)
{
	struct termios	term;
	char			**env;
	int				syntax;
	static int		s_save;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	env = NULL;
	syntax = 0;
	s_save = 0;
	env = main_init(environ, env);
	tcgetattr(0, &term);
	process_input(env, term, syntax, &s_save);
	ft_malloc(0, 1);
	return (0);
}
