#include "../mini.h"

t_symbols count_symbols(t_token *list)
{
	t_symbols s;

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
