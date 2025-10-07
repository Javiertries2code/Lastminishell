#include "../mini.h"

int execute_execve(t_token *list, t_data *data)
{
	char *cmd_path;
	char **cmd_arg;
	char **all_env;

	cmd_path = get_cmd_path(data->env_head, list->value);
	cmd_arg = list_cmd_arg(list);
	all_env = join_all_envp(data->env_head);
	if (execve(cmd_path, cmd_arg, all_env) == -1)
	{
		printf("Failed execve\n");
		free_exec_resources(cmd_path, cmd_arg, all_env);
		return (-1);
	}
	free_exec_resources(cmd_path, cmd_arg, all_env);
	return (0);
}

int handle_heredoc(t_token *list, int *heredoc_fd)
{
	int pipefd[2];
	char *line;

	if (!list)
	{
		*heredoc_fd = -1;
		return (0);
	}
	// Buscar el token de heredoc y obtener el delimitador
	while (list && !(list->token_op == HEREDOC && list->next && list->next->token_op == STRING))
	{
		list = list->next;
	}
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

	// Leer líneas hasta encontrar el delimitador
	while (1)
	{
		line = readline("> ");
		if (strcmp(line, list->next->value) == 0)
		{
			free(line);
			break;
		}

		// Escribir al pipe
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}

	close(pipefd[1]);		 // Cerrar escritura
	*heredoc_fd = pipefd[0]; // Guardar fd de lectura

	return (1); // Hay heredoc
}

int pipex(t_token **list, t_data *data, int current, int prev_pipe)
{
	t_token *cmd;
	int err;
	int pipefd[2];
	int heredoc_fd;
	int has_heredoc;
	int createpipe;
	pid_t pid;

	createpipe = current < data->num_comands - 1;
	heredoc_fd = -1;
	err = 0;

	// NUEVO: Manejar heredoc ANTES del fork
	has_heredoc = handle_heredoc(list[current], &heredoc_fd);
	if (has_heredoc == -1)
		return (-1);

	if (createpipe && pipe(pipefd) == -1)
	{
		perror("pipe");
		if (heredoc_fd != -1)
			close(heredoc_fd);
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (createpipe)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		if (heredoc_fd != -1)
			close(heredoc_fd);
		return (-1);
	}

	if (pid == 0)
	{
		// Child process

		// PRIORIDAD: heredoc > prev_pipe
		if (heredoc_fd != -1)
		{
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
			if (prev_pipe != -1)
				close(prev_pipe); // Ya no lo necesitamos
		}
		else if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}

		if (createpipe)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			close(pipefd[0]);
		}

		if (check_redirs(list[current]))
		{
			int log;
			err = create_redir(list[current]);
			if (err)
			{
				log = open("Log", O_CREAT | O_APPEND | O_WRONLY, 0644);
				write(log, "Error!!\n", 8);
				close(log);
				exit(1);
			}
		}
		cmd = get_cmd_from_list(list[current]);
		if (cmd && cmd->token_op == UNDEFINED)
			return (exit_with_token_error(data, get_cmd_from_list(list[current]), "Command not found"));

		if (cmd && execute_execve(cmd, data) == -1)
			return (exit_with_error(data, "EXECVE ERROR"));

		exit(EXIT_SUCCESS);
	}
	else
	{
		// Parent process

		// Cerrar heredoc_fd en el padre
		if (heredoc_fd != -1)
			close(heredoc_fd);

		if (prev_pipe != -1)
			close(prev_pipe);

		if (createpipe)
		{
			close(pipefd[1]);
			pipex(list, data, current + 1, pipefd[0]);
			close(pipefd[0]);
		}
		else
		{
			waitpid(pid, &sig, 0);
		}

		if (createpipe)
			waitpid(pid, &sig, 0);
	}

	return (0);
}
