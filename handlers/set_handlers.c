/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 00:03:11 by havr              #+#    #+#             */
/*   Updated: 2025/11/10 00:05:15 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	handler_ct_slash(int signal)
{
	(void)signal;
	print("handle slash  does nothing aparently");
	print("not in father not in son");
	return ;
}

void	handle_heredoc_ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("CTRL-C PRESSED-HEREDOC\n", 0);
	rl_redisplay();
}

void	handler_ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("CTRL-C PRESSED, I do Exit, but gotta be rmoved\n", 0);
	rl_redisplay();
	exit(0);
}

void	set_handlers(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &handler_ct_slash;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &handler_ctrl_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
