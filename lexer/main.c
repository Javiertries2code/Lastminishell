 #include "../mini.h"

int		sig = 0;

static void cut_init_data(t_data **data, char **envp, int *i){

	*i =0;
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	(*data)->env_head = (t_env *)ft_calloc(1, sizeof(t_env));
	(*data)->env_expr = NULL;
	copy_env((*data)->env_head, envp);


}

static void set_void_args(int *argc, char **argv){
	(void)*argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	int		i;

	set_void_args(&argc, argv);
	cut_init_data(&data, envp, &i);
	if (isatty(STDIN_FILENO))
	{
		set_handlers();
		while (1)
		{
			line = readline("minishell$ ");
			if (!empty(&line, data))
			{
				if (*line)
					add_history(line);
				if (check_initial_errors(data, line) == 0)
				{
					data->commands = ft_split_quotes(line, '|');
					if (line != NULL)
						free(line);
					for (i = 0; data->commands[i]; i++)
					{
						expand_var(i, data);
					}
					data->num_comands = i;
					tokenize(data);
					if (data->error_red == NULL && command_errors(data) == 0)
						manage_mini(data->tokens, data);
					if (data->error_red != NULL)
					{
						ft_putstr(SYNTAX_ERR);
						ft_putstr(data->error_red);
						write(1,"\n", 1);
						free(data->error_red);
						data->error_red = NULL;

					}
					free_split_tripoint(&data->commands);
					if (data->tokens)
					{
						free_command_info(data);
						data->tokens = NULL;
					}
				}
				else
					print_debug("Return no 0 check inital errors\n");
			}
		}
	}
	else
	{
		print("NOT a TTY\n");
	}
	if (data)
		free_all_data(data, assign_sig(0));
	return (0);
}
