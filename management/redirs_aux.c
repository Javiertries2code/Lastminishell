/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:04:45 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 17:11:35 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_symbols	count_symbols(t_token *list)
{
	t_symbols	s;

	s.forwd = 0;
	s.backwd = 0;
	s.append = 0;
	s.heredoc = 0;
	while (list)
	{
		if (list->token_op == RED_FORWD)
			s.forwd++;
		if (list->token_op == RED_BACKWD)
			s.backwd++;
		if (list->token_op == APPEND)
			s.append++;
		if (list->token_op == HEREDOC)
			s.heredoc++;
		list = list->next;
	}
	return (s);
}

int	remaining_out_counter(t_token *list)
{
	if (list->token_op == RED_FORWD)
		return (count_remaining_redirs(list->next, list->token_op)
			+ count_remaining_redirs(list->next, APPEND));
	return (count_remaining_redirs(list->next, list->token_op)
		+ count_remaining_redirs(list->next, RED_FORWD));
}
