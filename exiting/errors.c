#include "../mini.h"

/**
 * @brief Intending to free the input line related data uniquely
 * and to keep executing
 *
 * @param data
 * @param err_code
 */
void	free_command_info(t_data *data, int exit_code)
{
	if (!data)
		return ;
	free_str_safe(&data->str);
	if (data->commands)
		free_split_tripoint(&data->commands);
	free_str_safe(&data->tmp_var_name);
	if (data->tmp_var_expanded)
	{
		free(data->tmp_var_expanded);
		data->tmp_var_expanded = NULL;
	}
	data->tmp_var_len = 0;
	free_all_tokens(data);
	free_null_void((void **)&data->command_set);
	free_null_void(&data->l_back);
	free_null_void(&data->l_ff);
	free_null_void(&data->l_for);
	free_null_void(&data->l_hd);
	assign_sig(exit_code);
}

int	return_error(int err_code, char *caller, t_data *data)
{
	print_debug(caller);
	free_command_info(data, err_code);
	return (assign_sig(err_code));
}

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
int	check_initial_errors(t_data *data, char *line)
{
	char	*trimmed;

	if (quotes_balanced(line) == false)
		return (return_error(WRONG_SYNTAX,
				" FROM check_initial_errors unmatched quotes", data));
	// exit_with_error(data, "syntax error: unmatched quotes");
	trimmed = ft_strtrim(line, "\t\n\r\f\v ");
	if (!ft_strcmp("exit", trimmed))
		exit(assign_sig(0));
	// print_debug("last char trimmed");
	// print_debug(trimmed);
	// write(1,&trimmed[ft_strlen(trimmed - 1)], 1);
	// write(1,"\n", 1);
	if (trimmed[0] == '|' || trimmed[ft_strlen(trimmed) - 1] == '|')
	{
		free_str_safe(&trimmed);
		return (return_error(WRONG_SYNTAX,
				" FROM check_initial_errors invalid pipe position", data));
		// exit_with_error(data, "syntax error: invalid pipe position");
	}
	free_str_safe(&trimmed);
	return (0);
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
int	check_tokens_comands(t_data *data, t_token *token)
{
	t_token	*current;
	int		error;

	current = token;
	error = 0;
	while (current)
	{
		error = check_pipes_reds(current);
		//
		// printf("check tokens error- %d\n ", error);
		//
		if (error != 0)
		{
			print("ERROR REDIRECTIONS FOUND\ngonna exit ");
			return (return_error(error, "cheack token comands", data));
		}
		current = current->next;
	}
	return (0);
}

/**
 * command_errors - Validates all command token arrays
 * @data: Main data structure containing program state
 *
 * Iterates through all token arrays in data->tokens and validates
 * each one for command syntax errors. Uses check_comands for validation.
 */
int	command_errors(t_data *data)
{
	int i;
	int error;

	error = 0;
	i = 0;
	while (i < data->num_comands)
	{
		// si te devuelve diferente de 0 ESA LINEA TIENE ERROR DE REDIRECCIONEs
		error = check_tokens_comands(data, data->tokens[i]);
		if (error != 0)
			return (error);
		i++;
	}
	return (0);
}