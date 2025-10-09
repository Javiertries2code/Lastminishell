#include "../mini.h"

// Global variable definition and initialization
int		sig = 0;

bool	empty(char **line, t_data *data)
{
	char	*trimmed;

	if (*line == NULL)
	{
		print("CTRL D");
		free_all_data(data);
	}
	if (!line || !*line)
		return (true);
	trimmed = ft_strtrim(*line, "\t\n\r\f\v ");
	free(*line);
	*line = trimmed;
	if (!*line || **line == '\0')
		return (true);
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	bool	run;
	char	*line;
	t_data	*data;
	int		i;

	run = true;
	i = 0;
	(void)argc;
	(void)argv;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->env_head = (t_env *)ft_calloc(1, sizeof(t_env));
	copy_env(data->env_head, envp);
	// print_list(env_head);
	// 	TODO Wrap everything in an if else to see if it tty
	// 	TODO terminal la shell con ctrl D, no hacer nada
	// 	pero lo de poner nueva linea
	// 	rl_on_new_line,
	// rl_replace_line, rl_redisplay,
	if (isatty(STDIN_FILENO))
	{
		// setting handlers. Gotta double check, i dont see why setting
		// them in everylook, instead of changind the set up especiffically
		// for the heredoc, with signal old, new
		set_handlers();
		while (1)
		{
			line = readline("minishell$ ");
			// this can be moved to empty line
			if (!empty(&line, data))
			{
				if (*line)
					add_history(line);
				check_initial_errors(data, line);
				data->commands = ft_split_quotes(line, '|');
				// moved this, it whould work
				if (line != NULL)
					free(line);
				//	data->expanded = (char **)malloc(sizeof(*data->commands));
				for (i = 0; data->commands[i]; i++)
				{
					expand_var(i, data);
				}
				data->num_comands = i;
				tokenize(data);
				if (command_errors(data) == 0)
				{
					print_debug("CORRECT INPUT\n");

					manage_mini(data->tokens, data);
				}
				else
					print_debug("FOUND ERROR FROM MAIN\n");
					
				free_split(data->commands);
				// print_tokens(data);
				data->commands = NULL;
				if (data->tokens)
				{
					free_command_info(data, OK_SYNTAX);
					data->tokens = NULL;
				}
			}
		}
	}
	else
	{
		print("NOT a TTY\n");
	}
	if (data)
		free_all_data(data);
	return (0);
}
