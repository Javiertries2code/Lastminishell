/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:43:03 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/10 12:44:04 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	execute_execve(t_token *list, t_data *data)
{
	char	*cmd_path;
	char	**cmd_arg;
	char	**all_env;

	cmd_arg = NULL;
	all_env = NULL;
	if (list->token_op != BINARY)
		cmd_path = get_cmd_path(data->env_head, list->value);
	else
		cmd_path = ft_strdup(list->value);
	if (!cmd_path)
		return (free_exec_resources(cmd_path, cmd_arg, all_env, 1));
	if (list->token_op == BINARY && access(cmd_path, F_OK) == -1)
		return (free_exec_resources(cmd_path, cmd_arg, all_env, -2));
	cmd_arg = list_cmd_arg(list);
	all_env = join_all_envp(data->env_head);
	if (execve(cmd_path, cmd_arg, all_env) == -1)
		return (free_exec_resources(cmd_path, cmd_arg, all_env, -1));
	return (free_exec_resources(cmd_path, cmd_arg, all_env, 0));
}

int	handle_heredoc(t_token *list, int *heredoc_fd)
{
	int		pipefd[2];

	if (!list)
	{
		*heredoc_fd = -1;
		return (0);
	}
	while (list && !(list->token_op == HEREDOC
			&& list->next && list->next->token_op == STRING))
		list = list->next;
	if (!list || !list->next || !list->next->value)
	{
		*heredoc_fd = -1;
		return (0);
	}
	if (pipe(pipefd) == -1)
	{
		perror("heredoc pipe");
		return (-1);
	}
	heredoc(pipefd[1], list->next->value);
	close(pipefd[1]);
	*heredoc_fd = pipefd[0];
	return (1);
}

int	pipex(t_token **list, t_data *data, int current, int pp)
{
	t_pipes	pipesfd;

	pipesfd.prev_pipe = pp;
	pipesfd.createpipe = current < data->num_comands - 1;
	pipesfd.heredoc_fd = -1;
	pipesfd.has_heredoc = handle_heredoc(list[current], &pipesfd.heredoc_fd);
	if (pipesfd.has_heredoc == -1)
		return (-1);
	if (pipesfd.createpipe && pipe(pipesfd.pipefd) == -1)
	{
		perror("pipe");
		if (pipesfd.heredoc_fd != -1)
			close(pipesfd.heredoc_fd);
		return (-1);
	}
	if (builtin_types(data, list, current, pipesfd))
		return (0);
	post_fork(data, list, current, pipesfd);
	return (0);
}
