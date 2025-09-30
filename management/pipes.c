#include "../mini.h"

extern	int	SIG;

int	execute_execve(t_token *list, t_data *data)
{
	char	*cmd_path;
	char	**cmd_arg;
	char	**all_env;

	cmd_path = get_cmd_path(data->env_head, list->value);
	cmd_arg = list_cmd_arg(list);
	all_env = join_all_envp(data->env_head);
	if (execve(cmd_path, cmd_arg, all_env) == -1)
	{
		printf("Failed execve\n");
		return (-1);
	}
	free_exec_resources(cmd_path, cmd_arg, all_env);
	return (0);
}

/* 
		> fd del archivo de salida
		< char *del arg
		>> fd dela archivo de salida abierto en append
		<< readline + char *(strjoin arg)
*/

int pipex(t_token **list, t_data *data, int current, int prev_pipe)
{
	int		err;
	int 	pipefd[2];
	int 	createpipe;
	pid_t	pid;

	createpipe = current < data->num_comands - 1;
	err = 0;
	if (createpipe && pipe(pipefd) == -1)
	{
		perror("pipe");
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
		return (-1);
	}

	if (pid == 0)
	{
		// Child process
		if (prev_pipe != -1)
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
		else
		{
			// Para el último comando, stdout se queda como está
		}
		if (check_redirs(list[current]))
		{
			int	log;

			err = create_redir(list[current]);
			if (err)
			{
				log = open("Log", O_CREAT | O_APPEND | O_WRONLY, 0644);
				write(log, "Error!!\n", 8);			// Quitar para version de entrega (DEBUG)
				close(log);
				return 1;
			}
		}
		// Ejecutar el comando
		if (execute_execve(get_cmd_from_list(list[current]), data) == -1)
		{
			return (exit_with_error(data, "EXECVE ERROR"));
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Parent process
		if (prev_pipe != -1)
		{
			close(prev_pipe);
		}

		if (createpipe)
		{
			close(pipefd[1]); // Cerrar el extremo de escritura en el padre
			// Llamada recursiva para el siguiente comando
			pipex(list, data, current + 1, pipefd[0]);
			close(pipefd[0]); // Cerrar el extremo de lectura después del uso
		}
		else
		{
			// Último comando - esperar a que termine
			waitpid(pid, &SIG, 0);
		}

		// Esperar al proceso hijo actual si no es el último
		if (createpipe)
		{
			waitpid(pid, &SIG, 0);
		}
	}

	return (0);
}
