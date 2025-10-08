#include "../mini.h"

//int		sig = 0;

void	handler_ct_slash(int signal)
{
	(void)signal;
	print("handle slash  does nothing aparently");
	print("not in father not in son");
	return ;
}

void	handle_heredoc_ctrl_c(int signal)
{
	print("handle heredoc, pending");
	// TODO pending handler heredoc
	// TODO pending handler heredoc
	// ain sure what i gotta do to be honest.
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("CTRL-C PRESSED-HEREDOC\n", 0);
	rl_redisplay();
}
void	handler_ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("CTRL-C PRESSED, I do Exit, but gotta be rmoved\n", 0);
	rl_redisplay();
	//remove exit
	exit(0);
}

void	get_heredoc_input(char *delimiter, char *str, t_data *data)
{
	char	*line;
	void	(*old_handler)(int);
	char	*tmp;
	size_t	tmp_len;

	// Save current handler and set one use handler for the heredoc,
	// down there it is reset the handler to the standard one.
	old_handler = signal(SIGINT, handle_heredoc_ctrl_c);
	while (1)
	{
		tmp_len = 0;
		line = readline("HEREDOC> ");

		if (line == NULL)
	{
		print("CTRL D");
		free_all_data(data);
	}
		// allocating memory for a \n plus the previos line, concat and free
		if (!line) // Ctrl+D pressed
		{
			write(STDOUT_FILENO, "\n", 1);
			tmp_len = 1 + ft_strlen(str) + 1;
			tmp = ft_calloc(tmp_len, sizeof(char));
			tmp[0] = '\n';
			ft_strlcat(tmp, str, tmp_len);
			free(str);
			str = tmp;
			break ;
		} // allocating, concat and free
		else if (line)
		{
			tmp_len = ft_strlen(line) + ft_strlen(str) + 1;
			tmp = ft_calloc(tmp_len, sizeof(char));
			tmp = (void *)ft_memcpy(tmp, line, ft_strlen(line));
			ft_strlcat(tmp, str, tmp_len);
			free(str);
			str = tmp;
			break ;
		}
		else if (!ft_strncmp(line, delimiter, ft_strlen(line)))
		{
			//i think it gotta be strlen line, as in bash, if it happens u wrte more
			//, it doesnt take the delimiter
			free(line);
			break ;
		}
		if (line)
			free(line);
	}
	signal(SIGINT, old_handler);
}
void	set_handlers()
{
	struct sigaction sa;

	sa.sa_handler = &handler_ct_slash;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &handler_ctrl_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

}