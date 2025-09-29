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

int create_redir(t_token *list)
{
	t_token		*err;
	t_symbols	s;

	err = 0;
	s = count_symbols(list);
	if (s.forwd || s.append)
	{
		err = redir_forwd_append(list, &s);
		if (err->token_op == RED_FORWD || err->token_op == APPEND)
			return (token_with_error(SYNTAX_ERR, "newline"));
		if (err->next && err->next->token_op != STRING)
			return (token_with_error(SYNTAX_ERR, err->next->value));
	}
	if (s.backwd)
	{
		
	}
	if (s.heredoc)
	{

	}
	return (0);
}