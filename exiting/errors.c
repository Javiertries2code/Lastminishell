#include "../mini.h"

void	check_initial_errors(t_data *data, char *line)
{
	char	*trimmed;

	if (quotes_balanced(line) == false)
		exit_with_error(data, "syntax error: unmatched quotes");
	trimmed = ft_strtrim(line, "\t\n\r\f\v ");
	if (trimmed[0] == '|' || trimmed[ft_strlen(trimmed)] == '|')
	{
		free_null(trimmed);
		exit_with_error(data, "syntax error: invalid pipe position");
	}
	free_null(trimmed);
}
bool	check_comands(t_data *data, t_token *token)
{
	t_token	*current;
	int		error;

    current = token;
	error = 0;
	while (current)
	{
		error = check_pipes_reds(current);
		current = current->next;
		if (error)
			exit_with_error(data, "Error checking commands");
	}
	return (true);
}
void	command_errors(t_data *data)
{
	int i;

	i = 0;
	while (!check_comands(data, data->tokens[i++]))
		; // empty loop :-)
}