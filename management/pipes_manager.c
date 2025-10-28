#include "../mini.h"

void	post_fork(t_data *data, t_token **list, int current, t_pipes pipes)
{
    pipes.pid = fork();
	if (pipes.pid == -1)
		error_fork(pipes.createpipe, pipes.pipefd, pipes.heredoc_fd);
	if (pipes.pid == 0)
	{
		heredoc_prev_pipe(pipes.heredoc_fd, pipes.prev_pipe);
		piper(pipes.createpipe, pipes.pipefd);
		redir_manager(data, list, current);
	}
	else
		parent_process(data, list, current, pipes);
}

int	builtin_types(t_data *data, t_token **list, int current, t_pipes pipes)
{
	t_token	*cmd;

	cmd = get_cmd_from_list(list[current]);
	if (cmd && cmd->token_op == BUILTIN && !pipes.createpipe && pipes.prev_pipe == -1 &&
		(!ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "export") ||
		 !ft_strcmp(cmd->value, "cd") || !ft_strcmp(cmd->value, "exit")))
	{
		builtin_manager(cmd, data);
		if (pipes.heredoc_fd != -1)
			close(pipes.heredoc_fd);
		if (current < data->num_comands - 1)
		{
			pipex(list, data, current + 1, -1);
			return (1);
		}
		return (1);
	}
	return (0);
}