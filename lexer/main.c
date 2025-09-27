#include "../mini.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->env_head = (t_env *)ft_calloc(1, sizeof(t_env));
	copy_env(data->env_head, envp);
	// print_list(env_head);

// 	TODO Wrap everything in an if else to see if it tty

// 	TODO for before running it all, so the signall will kill the child process
// 			no memory isues as its a virtual copy
	
// 	TODO terminal la shell con ctrl D, no hacer nada
// 	pero lo de poner nueva linea 
// 	rl_on_new_line,
// rl_replace_line, rl_redisplay,



	while (1)
	{
		line = readline("minishell$ ");
		if (!line) // Ctrl+D
			exiting(data,"Got control D signal") ;
		if (*line)
			add_history(line);
		check_initial_errors(data, line);
		if (quotes_balanced(line) == false)
		{
			printf("MALAS COMILLAS PRINGAO HAVE TO FREE ");
			return (0);
		}
		data->commands = ft_split_quotes(line, '|');
		//	data->expanded = (char **)malloc(sizeof(*data->commands));
		for (i = 0; data->commands[i]; i++)
		{
			expand_var(i, data);
		}
		data->num_comands = i;
		tokenize(data);
		//printing test
		print_tokens(data);
		if (line != NULL)
			free(line);
		//	execute_command(data);
		free_split(data->commands);
		data->commands = NULL;
	}
	free_data(data);
	return (0);
}
