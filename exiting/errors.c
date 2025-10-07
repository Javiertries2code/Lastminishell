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
        free_split(data->commands);
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


int return_error(int err_code, char *caller, t_data *data){
 	print_debug(caller);
	free_command_info(data, ERRLIST_SYNTAX);
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
void	check_initial_errors(t_data *data, char *line)
{
	char	*trimmed;

	if (quotes_balanced(line) == false)
		exit_with_error(data, "syntax error: unmatched quotes");
	trimmed = ft_strtrim(line, "\t\n\r\f\v ");
	if (!ft_strcmp("exit", trimmed))
		exit(assign_sig(0));
	if (trimmed[0] == '|' || trimmed[ft_strlen(trimmed)] == '|')
	{
		free_null(&trimmed);
		exit_with_error(data, "syntax error: invalid pipe position");
	}
	if(trimmed != NULL)
		free_null(&trimmed);
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
		{
			print("ERROR REDIRECTIONS FOUND\ngonna exit ");
			return (return_error(1, "cheack token comands", data));
			
		}
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
	while (!check_tokens_comands(data, data->tokens[i]) && i < data->num_comands)
		; // empty loop :-)
}