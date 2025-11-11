/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:07:35 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 17:13:36 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	process_output_redir(t_token *list, int is_last)
{
	int	fd;
	int	flags;

	if (!list->next || list->next->token_op != STRING)
		return (token_with_error(SYNTAX_ERR, "newline"));
	if (list->token_op == APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	else
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	fd = open(list->next->value, flags, 0644);
	if (fd < 0)
		return (token_with_no_path(list->next->value));
	if (is_last)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	process_input_redir(t_token *list, int is_last)
{
	int	fd;

	if (!list->next || list->next->token_op != STRING)
		return (token_with_error(SYNTAX_ERR, "newline"));
	fd = open(list->next->value, O_RDONLY);
	if (fd < 0)
		return (token_with_no_path(list->next->value));
	if (is_last)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	count_remaining_redirs(t_token *list, t_token_op type)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token_op == type)
			count++;
		list = list->next;
	}
	return (count);
}

int	create_redir(t_token *list)
{
	int	remaining_out;
	int	remaining_in;
	int	ret;

	while (list)
	{
		if (list->token_op == RED_FORWD || list->token_op == APPEND)
		{
			remaining_out = remaining_out_counter(list);
			ret = process_output_redir(list, remaining_out == 0);
			if (ret != 0)
				return (ret);
		}
		else if (list->token_op == RED_BACKWD)
		{
			remaining_in = count_remaining_redirs(list->next, RED_BACKWD);
			ret = process_input_redir(list, remaining_in == 0);
			if (ret != 0)
				return (ret);
		}
		list = list->next;
	}
	return (0);
}
