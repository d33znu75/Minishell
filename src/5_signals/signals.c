/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:42:12 by rhmimchi          #+#    #+#             */
/*   Updated: 2024/11/04 15:17:36 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_sigpipe(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
}

void	sigint_handler(int sig)
{
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		return ;
	}
}

void	initialize_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
