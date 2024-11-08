# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 00:40:47 by rhmimchi          #+#    #+#              #
#    Updated: 2024/11/04 17:40:46 by rhmimchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

PURPLE = \033[35m
RESET = \033[0m
BOLD = \033[1m

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include
HEADERS_DIR = ./headers
SRC_DIR = ./src
OBJ_DIR = ./obj
LIBRARY_DIR = ./libft
DEPS_DIR = $(OBJ_DIR)

CFLAGS = -g -fsanitize=address #-Wall -Wextra -Werror 
HFLAGS = -I$(READLINE_I)
LFLAGS = -L$(LIBRARY_DIR) -lft -L$(READLINE_L) -lreadline

NAME = minishell

SOURCES =  $(SRC_DIR)/0_initialization/env_init.c \
           $(SRC_DIR)/1_syntax_error_checking/syntax_error_checker.c \
           $(SRC_DIR)/1_syntax_error_checking/syntax_error_checker_utils.c \
           $(SRC_DIR)/2_tokenizer/tokenizer.c \
           $(SRC_DIR)/2_tokenizer/tokenizer_utils.c \
           $(SRC_DIR)/3_parser/parser.c \
           $(SRC_DIR)/3_parser/parser_utils.c \
           $(SRC_DIR)/3_parser/parser_commands.c \
           $(SRC_DIR)/3_parser/parser_node_args.c \
           $(SRC_DIR)/3_parser/parser_operators.c \
           $(SRC_DIR)/3_parser/parser_hdoc_utils.c \
           $(SRC_DIR)/3_parser/parser_hdoc_utils2.c \
           $(SRC_DIR)/3_parser/parser_hdoc_delimiter.c \
           $(SRC_DIR)/3_parser/parser_hdoc.c \
           $(SRC_DIR)/3_parser/quotes_handler1.c \
           $(SRC_DIR)/3_parser/quotes_handler2.c \
           $(SRC_DIR)/4_expander/expander1.c \
           $(SRC_DIR)/4_expander/expander2.c \
           $(SRC_DIR)/6_executer/execution_utils.c \
           $(SRC_DIR)/6_executer/execution.c \
           $(SRC_DIR)/6_executer/exec_bin.c \
           $(SRC_DIR)/6_executer/exec_bin_utils.c \
           $(SRC_DIR)/6_executer/exec_pipe.c \
           $(SRC_DIR)/6_executer/exec_hdoc.c \
           $(SRC_DIR)/6_executer/execute_command.c \
           $(SRC_DIR)/6_executer/execution_dollar.c \
           $(SRC_DIR)/6_executer/get_splits.c \
           $(SRC_DIR)/6_executer/execute_tokens_redir.c \
           $(SRC_DIR)/6_executer/execute_tokens_redir_utils.c \
           $(SRC_DIR)/6_executer/execute_tokens_redir_utils2.c \
           $(SRC_DIR)/5_signals/signals.c \
           $(SRC_DIR)/7_builtins/builtins.c \
           $(SRC_DIR)/7_builtins/builtins_2.c \
           $(SRC_DIR)/7_builtins/export.c \
           $(SRC_DIR)/7_builtins/export_utils.c \
           $(SRC_DIR)/7_builtins/export_utils2.c \
           $(SRC_DIR)/7_builtins/export_append.c \
           $(SRC_DIR)/7_builtins/export_var.c \
           $(SRC_DIR)/7_builtins/echo.c \
           $(SRC_DIR)/7_builtins/cd.c \
           $(SRC_DIR)/7_builtins/exit.c \
           $(SRC_DIR)/7_builtins/exit_utils.c \
           $(SRC_DIR)/7_builtins/ft_unset.c \
           $(SRC_DIR)/7_builtins/ft_pwd.c \
           $(SRC_DIR)/main.c \
           $(SRC_DIR)/main_utils.c

LIBRARY = $(LIBRARY_DIR)/libft.a
OBJS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: banner $(NAME)

banner:
	@printf "$(PURPLE)$(BOLD)"
	@printf "\n"
	@printf "     ███╗   ███╗██╗███╗   ██╗██╗██████╗  █████╗ ███████╗██╗  ██╗     \n"
	@printf "     ████╗ ████║██║████╗  ██║██║██╔══██╗██╔══██╗██╔════╝██║  ██║     \n"
	@printf "     ██╔████╔██║██║██╔██╗ ██║██║██████╔╝███████║███████╗███████║     \n"
	@printf "     ██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗██╔══██║╚════██║██╔══██║     \n"
	@printf "     ██║ ╚═╝ ██║██║██║ ╚████║██║██████╔╝██║  ██║███████║██║  ██║     \n"
	@printf "     ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝     \n"
	@printf "                                                                                                    \n"
	@printf "$(RESET)"

$(NAME): $(LIBRARY) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(HFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS_DIR)/minishell.h $(HEADERS_DIR)/libft.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBRARY): banner
	@$(MAKE) -C $(LIBRARY_DIR)

clean: banner
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBRARY_DIR) clean

fclean: banner clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBRARY_DIR) fclean

re: banner fclean all

.PHONY: clean banner