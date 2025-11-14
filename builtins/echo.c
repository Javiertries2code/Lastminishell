/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:39 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 17:42:48 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static bool	is_n_flag(t_token *list)
{
	size_t	i;

	if (!list || !list->value || list->value[0] != '-')
		return (false);
	if (!list->value[1])
		return (false);
	i = 1;
	while (list->value[i] && list->value[i] == 'n')
		i++;
	if (list->value[i])
		return (false);
	return (true);
}

static bool	is_operator(t_token *token)
{
	if (!token)
		return (false);
	return (token->token_op == RED_FORWD
		|| token->token_op == RED_BACKWD
		|| token->token_op == APPEND
		|| token->token_op == HEREDOC);
}

int	ft_echo(t_token *list)
{
	bool	new_line;
	bool	first;

	new_line = true;
	list = list->next;
	while (list && is_n_flag(list))
	{
		new_line = false;
		list = list->next;
	}
	first = true;
	while (list && !is_operator(list))
	{
		if (list->token_op == STRING)
		{
			if (!first)
				ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(list->value, STDOUT_FILENO);
			first = false;
		}
		list = list->next;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (assign_sig(0));
}
