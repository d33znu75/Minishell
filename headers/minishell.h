/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:52:52 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 15:10:55 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <sys/syslimits.h>
# include <sys/stat.h>
# include <string.h>

# define UNCLOSED_QUOTES "minibash: Syntax error: unclosed quotes.\n"
# define MISPLACED_PIPE "minibash: Syntax error: misplaced pipe `|`.\n"
# define INVALID_REDIRECTIONS \
	"minibash: syntax error near unexpected token `newline'\n"
# define UNSUPPORTED_OPERATORS \
	"minibash: syntax error near unexpected token `newline'\n"
# define MALLOC_FAILED "minibash: Malloc Failed\n"
# define HDOC_PIPE_ERROR "ERROR: execute_hdoc: pipe\n"
# define HDOC_FORK_ERROR "ERROR: execute_hdoc: fork\n"
# define FILE_NOT_FOUND ": No such file or directory\n"
# define EXP_ERR ": not a valid identifier\n"
# define SYNTAX_ERR "minibash : syntax error near unexpected token `newline'\n"

int	g_exit_status;

typedef struct s_delimiter
{
	char				*value;
	bool				has_quotes;
	struct s_delimiter	*next;
}	t_delimiter;

typedef enum e_token_type
{
	TOKEN_LITERAL,
	TOKEN_PIPE,
	TOKEN_RDIR_IN,
	TOKEN_RDIR_OUT,
	TOKEN_RDIR_APPEND,
	TOKEN_HDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	bool				syntax_error;
	struct s_token		*next_token;
	struct s_token		*prev_token;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				*heredoc_content;
	t_delimiter			*delimiters;
}	t_ast_node;

typedef struct s_handler
{
	int		i;
	int		j;
	int		x;
	char	*new_str;
	char	**arr;
}	t_handler;

typedef struct s_dollar_handler
{
	int		len;
	int		x;
	int		z;
	int		z1;
	char	**splits;
	char	**env;
	char	**tmp_splits;
	char	**tmp_sp2;
}	t_dollar_handler;

typedef struct s_get_splits
{
	char		**splits;
	char		**get_splits;
	int			z;
	int			b;
	int			d;
	t_ast_node	*node;
	char		**env;
}	t_get_splits;

typedef struct s_context
{
	t_token	*current;
	t_token	*last_valid;
	char	**env;
}	t_context;

char		**env_init(char **environ);
char		**env_init_null(void);
char		**set_exit_status(char **env, int status);
void		ctrl_d_handler(char **env);
char		**main_g_exit(char **env);
char		**main_init(char **environ, char **env);
int			has_syntax_error(char *cmd_line, char **env);
bool		has_mismatched_quotes(char *cmd_line);
bool		has_misplaced_pipes(char *cmd_line);
bool		has_unsupported_operators(char *cmd_line);
t_token		*create_token(t_token_type type, char *value);
void		tokens_list_append(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
t_token		*new_token(t_token_type type, char *value, \
				t_token **tokens, char **splitted_args);
t_token		*tokenize_redirections(t_token **tokens, \
				char *token, char **splitted_args);
t_token		*tokenize_arg(t_token **tokens, char **splitted_args, char *arg);
t_token		*tokenizer(char *cmd_line);
t_ast_node	*new_ast_node(t_token_type type);
void		free_ast_tree(t_ast_node *node);
int			get_precedence(t_token_type type);
int			count_args(t_token *current);
t_ast_node	*handle_redirect_token(t_ast_node **root, \
	t_token **tokens, char **env);
t_ast_node	*handle_redirection(t_ast_node *left, t_token **tokens, char **env);
t_ast_node	*create_file_node(t_token **tokens, char **env);
t_ast_node	*handle_pipes(t_ast_node *left, \
	t_token **tokens, int precedence, char **env);
void		free_ast_args(t_ast_node *node);
int			append_arg(t_ast_node *node, char *arg);
char		**ft_realloc_args(char **args, int current_size, int new_size);
int			append_literal_args(t_ast_node *left, t_token **tokens);
void		heredoc_signal_handler(int sig);
int			run_heredoc(t_ast_node *node, char **env);
t_ast_node	*handle_heredocs(t_token **tokens, char **env);
void		add_delimiter(t_ast_node *node, char *value);
void		free_delimiters_list(t_delimiter *delimiters);
void		print_syntax_error(t_token *token);
t_ast_node	*init_heredoc_node(void);
char		*join_content(char *content, char *line);
char		*read_pipe_content(int fd);
t_context	create_context(t_token *current, t_token *last_valid, char **env);
char		*read_heredoc_content(t_delimiter *delimiters, char **env);
int			process_heredoc_tokens(t_ast_node **node, \
				t_token **tokens, t_context *context);
t_ast_node	*handle_literal_token(t_ast_node **root, \
					t_ast_node **cmd_node, t_token **tokens, char **env);
t_ast_node	*parse_command_with_redirects(t_token **tokens, char **env);
t_ast_node	*create_command_node(t_token **tokens, char **env);
t_ast_node	*parse_commands(t_token **tokens, char **env);
t_ast_node	*parse_operators(t_ast_node *left, t_token **tokens, \
	int precedence, char **env);
t_ast_node	*parse_expression(t_token **tokens, int precedence, char **env);
t_ast_node	*parser(t_token **tokens, char **env);
void		generate_ast_graph(t_ast_node *first_node);
void		print_tokens(t_token *tokens);
void		initialize_signals(void);
void		handle_sigpipe(int sig);
char		**execute_ast(t_ast_node *node, char **env, int *s_save);
char		**execute_command(t_ast_node *node, char **env, \
								int skip, int *s_save);
void		token_pipe(t_ast_node *node, char **env, int *s_save);
char		**execute_command_in_bin(char **args, char **env);
void		execute_hdoc(t_ast_node *node, char **env);
void		set_status(char **env, int x_exit_status);
int			has_slash(char *str);
void		handle_slash(char **args, char **env, char *cmd);
char		**execute_command_in_bin(char **args, char **env);
void		token_rdir_in(t_ast_node *node, char **env, int *s_save);
void		token_rdir_out(t_ast_node *node, char **env, int *s_save);
void		token_rdir_append(t_ast_node *node, char **env, int *s_save);
t_ast_node	*find_command_node(t_ast_node *node);
int			apply_redirections(t_ast_node *node, int *last_in_fd,
				int *last_out_fd, char **env);
void		handle_redir(t_ast_node *node, char **env, int *s_save);
void		restore_std_fds(int saved_in, int saved_out);
void		setup_redirections(int last_in_fd, int last_out_fd);
char		**ft_cd(char **args, char **env);
void		ft_echo(char **args, char **env, int *s_save);
void		ft_pwd(char **env);
char		**ft_export(char **args, char **env);
char		**ft_unset(char **args, char **env);
void		ft_env(char **env);
void		ft_exit(char **args, char **env);
char		*get_env_var(char **env, char *var);
char		*ft_pwd_str(char **env);
int			check_env_var(char **env, char *var);
int			check_value_in_env(char **env, char *key);
char		**add_env_var(char **env, char *var);
char		**set_env_var(char **env, char *var, char *value);
char		*remove_quotes(char *str);
int			check_key_format(char *str);
void		ft_swap(char **a, char **b);
int			check_is_in_env(char **env, char *key);
int			ft_arglen(char **arr);
char		*handle_q(char *str);
char		*add_quotes(char *str);
int			check_value_in_env(char **env, char *value);
int			find_char(char *str, char c);
char		*ft_strjoin_c(char *s1, char c);
char		*handle_q2(char *str, char **env);
char		*expander(char *str, char **env);
char		*expander2(char *str, char **env);
void		exit_with_error(char *arg, char **env);
void		exit_max_long(char **args, char **env);
void		exit_min_long(char **args, char **env);
int			ft_strcasecmp(const char *s1, const char *s2);
int			only_dollar(char *str);
int			has_dollar(char *str);
char		**handle_dollar(char **splits, char **env, int len);
char		**ft_export_plus(char **args, char **env);
char		**export_with_args(char **args, char **env, int i, int exit_flag);
int			ft_is_echo(char **splits);
char		**get_splits(t_ast_node *node, char **env, int handler);
int			has_quotes(char *str);
char		*remove_the_quotes(char *str);
int			check_in_pwd(char **args, char **env);
void		forking_checkers(char **args, char **env, char **bins, char *cmd);
void		print_and_exit(char **env);

#endif