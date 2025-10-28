/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:07:35 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:08:43 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static t_token	*redir_forwd_append(t_token *list, t_symbols *s)
{
	int	fd;

	while (list)
	{
		if ((list->token_op == RED_FORWD || list->token_op == APPEND)
			&& list->next && list->next->token_op == STRING)
		{
			if (list->token_op == RED_FORWD)
			{
				printf("[DEBUG] Opening file for RED_FORWD: '%s' (pid=%d)\n", list->next->value, getpid());
				fd = open(list->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				printf("[DEBUG] Opened fd=%d for file '%s'\n", fd, list->next->value);
				s->forwd--;
			}
			else if (list->token_op == APPEND)
			{
				fd = open(list->next->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
				s->append--;
			}
			if (fd < 0)
				return (list->next);
			if (s->forwd + s->append == 0)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
				return (NULL);
			}
			close(fd);
		}
		else if ((list->token_op == RED_FORWD || list->token_op == APPEND)
			&& list->next && list->next->token_op != STRING)
			return (list->next);
		else if ((list->token_op == RED_FORWD || list->token_op == APPEND)
			&& !list->next)
			return (list);
		list = list->next;
	}
	return (NULL);
}

static t_token	*redir_backwd(t_token *list, t_symbols *s)
{
	int		fd;

	while (list)
	{
		if (list->token_op == RED_BACKWD && list->next && list->next->token_op == STRING)
		{
			fd = open(list->next->value, O_RDONLY);
			if (fd < 0)
				return (list->next);
			s->backwd--;
			if (s->backwd == 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
				return (NULL);
			}
		}
		else if (list->token_op == RED_BACKWD && list->next && list->next->token_op != STRING)
			return (list->next);
		else if (list->token_op == RED_BACKWD && !list->next)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int	create_redir(t_token *list)
{
	t_token		*err;
	t_symbols	s;
	t_token		*tmp;

	err = NULL;
	printf("[DEBUG create_redir] Starting, list=%p\n", (void*)list);
	tmp = list;
	while (tmp)
	{
		printf("[DEBUG] Token: op=%d, value=%p", tmp->token_op, (void*)tmp->value);
		if (tmp->value)
			printf(" '%s'", tmp->value);
		printf(", next=%p\n", (void*)tmp->next);
		tmp = tmp->next;
	}
	s = count_symbols(list);
	while (s.forwd || s.append || s.backwd || s.heredoc)
	{
		if (s.forwd || s.append)
		{
			err = redir_forwd_append(list, &s);
			if (err && err->token_op == RED_FORWD)
				return (token_with_error(SYNTAX_ERR, "newline"));
			else if (err && err->token_op == APPEND)
				return (token_with_error(SYNTAX_ERR, "newline"));
			else if (err && err->token_op == STRING)
				return (token_with_no_path(err->value));
		}
		if (s.backwd)
		{
			err = redir_backwd(list, &s);
			if (err && err->token_op == RED_BACKWD)
				return (token_with_error(SYNTAX_ERR, "newline"));
			else if (err && err->token_op == STRING)
				return (token_with_no_path(err->value));
		}
		if (s.heredoc)
		{
			s.heredoc--;
			return (0);
		}
	}
	return (0);
}
