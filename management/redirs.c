#include "../mini.h"

extern	int	SIG;

static int	get_forwd_fd(t_token *list)
{
	int	fd;

	while (list)
	{
		if (list->token_op == RED_FORWD && list->next)
		{
			fd = open(list->next->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		
	}
	
}

static int	get_backwd_fd(t_token *list)
{
	
}

static int	get_append_fd(t_token *list)
{
	
}

static int	get_heredoc_fd(t_token *list)
{
	
}

void	createpiper(t_token *list, int *pipefd)
{
	int	redirs;
	int	redfd;

	redirs = check_redirs(list);
	if (redirs == 1)
	{
		redfd = get_forwd_fd(list);
	}
	else if (redirs == 2)
	{
		redfd = get_backwd_fd(list);
	}
	else if (redirs == 3)
	{
		redfd = get_append_fd(list);
	}
	else if (redirs == 4)
	{
		redfd = get_heredoc_fd(list);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	redirs = 0;
}
