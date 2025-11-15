/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:44:50 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/10 12:46:19 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static int	save_and_redirect(t_token *list, int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = -1;
	*saved_stdout = -1;
	if (check_redirs(list))
	{
		*saved_stdin = dup(STDIN_FILENO);
		*saved_stdout = dup(STDOUT_FILENO);
		if (*saved_stdin == -1 || *saved_stdout == -1)
			return (-1);
		create_redir(list);
	}
	return (0);
}

int	builtin_types(t_data *data, t_token **list, int current, t_pipes pipes)
{
	t_token	*cmd;
	int		saved_stdin;
	int		saved_stdout;

	cmd = get_cmd_from_list(list[current]);
	if (cmd && cmd->token_op == BUILTIN
		&& !pipes.createpipe && pipes.prev_pipe == -1
		&& (!ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "export")
			|| !ft_strcmp(cmd->value, "cd") || !ft_strcmp(cmd->value, "exit")))
	{
		if (save_and_redirect(list[current], &saved_stdin, &saved_stdout) == -1)
			return (1);
		builtin_manager(cmd, data);
		restore_fds(saved_stdin, saved_stdout);
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
