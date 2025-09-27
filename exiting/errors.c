#include "../mini.h"

void	check_initial_errors(t_data *data, char *line)
{
	char	*trimmed;

	if (quotes_balanced(line) == false)
		exiting(data, "MALAS COMILLAS PRINGAO HAVE TO FREE ");
	trimmed = ft_strtrim(line, "\t\n\r\f\v "); // trimming all spaces
	if (trimmed[0] == '|' || trimmed[ft_strlen(trimmed)] == '|')
		exiting(data, "ESOS PIPESSSSSS");
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
			exiting(data, "Error checking commands");
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