#include "../mini.h"

static t_token	*redir_forwd_append(t_token *list, t_symbols *s)
{
	int	fd;

	while (list)
	{
		if ((list->token_op == RED_FORWD || list->token_op == APPEND) && list->next && list->next->token_op == STRING)
		{
			if (list->token_op == RED_FORWD)
			{
				fd = open(list->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				s->forwd--;
			}
			else if (list->token_op == APPEND)
			{
				fd = open(list->next->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
				s->append--;
			}
			if (s->forwd + s->append == 0)
			{	
				dup2(fd, STDOUT_FILENO);
				return (NULL);
			}
		}
		else if ((list->token_op == RED_FORWD || list->token_op == APPEND) && list->next && list->next->token_op != STRING)
			return (list->next);
		else if ((list->token_op == RED_FORWD || list->token_op == APPEND) && !list->next)
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

int create_redir(t_token *list)
{
	t_token		*err;
	t_symbols	s;

	err = NULL;
	s = count_symbols(list);
	while (s.forwd || s.append || s.backwd || s.heredoc)
	{
		if (s.forwd || s.append)
		{
			err = redir_forwd_append(list, &s);
			if (!err)
				err = NULL;
			else if (err->token_op == RED_FORWD || err->token_op == APPEND)
				return (token_with_error(SYNTAX_ERR, "newline"));
			else if (err->next && err->next->token_op != STRING)
				return (token_with_error(SYNTAX_ERR, err->next->value));
		}
		if (s.backwd)
		{
			err = redir_backwd(list, &s);
			if (!err)
				err = NULL;
			else if (err->token_op == RED_BACKWD)
				return (token_with_error(SYNTAX_ERR, "newline"));
			else if (err->next && err->next->token_op != STRING)
				return (token_with_error(SYNTAX_ERR, err->next->value));
			else if (err->next->token_op == STRING)
				return (token_with_no_path(err->next->value));
		}
		if (s.heredoc)
		{

		}
	}
	return (0);
}