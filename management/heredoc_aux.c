#include "../mini.h"

void	heredoc(int pipefd1, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (strcmp(line, eof) == 0)
		{
			free(line);
			break;
		}
		write(pipefd1, line, strlen(line));
		write(pipefd1, "\n", 1);
		free(line);
	}
}