#include "../mini.h"

t_symbols count_symbols(t_token *list)
{
	t_symbols s;

	s.forwd = 0;
	s.backwd = 0;
	s.append = 0;
	s.heredoc = 0;
	while (list)
	{
		if (list->token_op == RED_FORWD)
			s.forwd++;
		if (list->token_op == RED_BACKWD)
			s.backwd++;
		if (list->token_op == APPEND)
			s.append++;
		if (list->token_op == HEREDOC)
			s.heredoc++;
		list = list->next;
	}
	return (s);
}

void	get_heredoc_input(char *delimiter, char **str, t_data *data)
{
    char    *line;
    void    (*old_handler)(int);
    char    *tmp;
    size_t    tmp_len;

    // Save current handler and set one use handler for the heredoc,
    // down there it is reset the handler to the standard one.
    old_handler = signal(SIGINT, handle_heredoc_ctrl_c);
    while (1)
    {
        tmp_len = 0;
        line = readline("HEREDOC> ");

        if (!*line)
		{
			print("CTRL D");
			free_all_data(data);
		}
        // allocating memory for a \n plus the previos line, concat and free
        if (!line) // Ctrl+D pressed
        {
            write(STDOUT_FILENO, "\n", 1);
            tmp_len = 1 + ft_strlen(*str) + 1;
            tmp = ft_calloc(tmp_len, sizeof(char));
            tmp[0] = '\n';
            ft_strlcat(tmp, *str, tmp_len);
            free(*str);
            *str = tmp;
            break ;
        } // allocating, concat and free
        else if (line)
        {
            tmp_len = ft_strlen(line) + ft_strlen(*str) + 1;
            tmp = ft_calloc(tmp_len, sizeof(char));
            tmp = (void *)ft_memcpy(tmp, line, ft_strlen(line));
            ft_strlcat(tmp, *str, tmp_len);
            free(*str);
            *str = tmp;
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
