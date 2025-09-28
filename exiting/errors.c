#include "../mini.h"

/**
 * check_initial_errors - Validates initial syntax of input line
 * @data: Main data structure containing program state
 * @line: Input line to validate
 *
 * Performs initial syntax validation on the input line:
 * - Checks if quotes are properly balanced
 * - Verifies pipe positions are valid (not at start or end)
 * Exits with error if any validation fails.
 */
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

/**
 * check_comands - Validates command tokens for syntax errors
 * @data: Main data structure containing program state
 * @token: Token list to validate
 *
 * Iterates through the token list and checks for pipe and redirection
 * syntax errors using check_pipes_reds function.
 *
 * Return: true if all commands are valid, exits on error
 */
bool	check_tokens_comands(t_data *data, t_token *token)
{
	t_token	*current;
	int		error;

    current = token;
	error = 0;
	while (current)
	{
		error = check_pipes_reds(current);
		if (error != 0)
			exit_with_error(data, "Error checking commands");
		current = current->next;
	}
	return (true);
}

/**
 * command_errors - Validates all command token arrays
 * @data: Main data structure containing program state
 *
 * Iterates through all token arrays in data->tokens and validates
 * each one for command syntax errors. Uses check_comands for validation.
 */
void	command_errors(t_data *data)
{
	int i;

	i = 0;
	while (!check_tokens_comands(data, data->tokens[i++]))
		; // empty loop :-)
}