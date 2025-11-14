/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:44:12 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 17:45:51 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	error_fork(int createpipe, int pipefd[2], int heredoc_fd)
{
	perror("fork didnt work");
	if (createpipe)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (heredoc_fd != -1)
		close(heredoc_fd);
}

void	heredoc_prev_pipe(int heredoc_fd, int prev_pipe)
{
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
		if (prev_pipe != -1)
			close(prev_pipe);
	}
	else if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
}

void	piper(int createpipe, int pipefd[2])
{
	if (createpipe)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

void	redir_manager(t_data *data, t_token **list, int current)
{
	t_token	*cmd;

	if (check_redirs(list[current]))
		create_redir(list[current]);
	cmd = get_cmd_from_list(list[current]);
	if (cmd && cmd->token_op == UNDEFINED)
	{
		assign_sig(127);
		exit_with_token_error(data, cmd, "Command not found");
	}
	if (cmd && cmd->token_op == BUILTIN && builtin_manager(cmd, data) == -1)
		exit_with_error(data, "Error executing builtin");
	if (cmd && cmd->token_op == COMMAND && execute_execve(cmd, data) == -1)
		exit_with_error(data, "Error executing command");
	if (cmd && cmd->token_op == COMMAND && execute_execve(cmd, data) == -1)
	{
		assign_sig(2);
		exit_with_token_error(data, cmd, "No such file");
	}
	if (cmd && cmd->token_op == BINARY && execute_execve(cmd, data) == -2)
	{
		assign_sig(2);
		exit_with_token_error(data, cmd, "No such file");
	}
	exit(sig);
}

void	parent_process(t_data *data, t_token **list, int current, t_pipes pipes)
{
	int	status;

	if (pipes.heredoc_fd != -1)
		close(pipes.heredoc_fd);
	if (pipes.prev_pipe != -1)
		close(pipes.prev_pipe);
	if (pipes.createpipe)
	{
		close(pipes.pipefd[1]);
		pipex(list, data, current + 1, pipes.pipefd[0]);
		close(pipes.pipefd[0]);
	}
	else
		waitpid(pipes.pid, &status, 0);
	if (pipes.createpipe)
		waitpid(pipes.pid, &status, 0);
	if (WIFEXITED(status))
		sig = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sig = 128 + WTERMSIG(status);
}
