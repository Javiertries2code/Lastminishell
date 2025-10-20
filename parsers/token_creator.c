#include "../mini.h"

/**
 * @brief Evaluates a word and assigns the appropriate token type and value
 * @param data Main data structure containing all parsing information
 * @param token Token structure to be filled with evaluation results
 * @param word Input word to be evaluated
 * @param token_op Token operation type (currently unused)
 */
static void	eval(t_data *data, t_token *token, char *word, t_token_op token_op)
{
	char	*unquoted_word;
	char	*tmp;

	(void)token_op;
	tmp = remove_outer_quotes(word);
	unquoted_word = ft_strdup(tmp);
	free(tmp);
	if (word[0] == '\0')
	{
		free(unquoted_word);
		return ;
	}
	if (check_prev(data, token, word))
	{
		free(unquoted_word);
		return ;
	}
	if (eval_red(data, token, word))
	{
		free(unquoted_word);
		return ;
	}
	if (eval_builtin(data, token, unquoted_word))
	{
		token->value = unquoted_word;
		return ;
	}
	if(is_binary(data, token, unquoted_word))
	{
		ft_putnbr_fd(2009099, STDOUT_FILENO);
		token->value = unquoted_word;
		return ;
	}
	token->value = unquoted_word;
}

/**
 * @brief Adds a new token to the end of the token list for a specific row
 * @param data Main data structure containing token arrays
 * @param new New token to be added to the tail of the list
 */
void	add_to_tail(t_data *data, t_token *new)
{
	t_token	*current;

	current = data->tokens[new->row];
	while (current->next)
		current = current->next;
	new->pos = current->pos + 1;
	new->prev = current;
	new->next = NULL;
	current->next = new;
}

/**
 * @brief Loads word data into a token structure,
	creating new token if necessary
 * @param data Main data structure containing all parsing information
 * @param row Row index where the token should be placed
 * @param word Input word to be processed
 * @param token_op Token operation type to be assigned
 */
void	load_data(t_data *data, int row, char *word, t_token_op token_op)
{
	t_token	*new_token;
	char	*tmp;

	tmp = remove_outer_quotes(word);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return ;
	}
	free(tmp);
	if (data->tokens[row]->value == NULL && data->tokens[row]->next == NULL)
	{
		new_token = data->tokens[row];
		new_token->row = row;
		new_token->pos = 0;
	}
	else
	{
		new_token = ft_calloc(1, sizeof(t_token));
		new_token->row = row;
		add_to_tail(data, new_token);
	}
	eval(data, new_token, word, token_op);
}

/**
 * @brief Creates a new token by calling load_data function
 * @param data Main data structure containing all parsing information
 * @param row Row index where the token should be placed
 * @param word Input word to be processed
 * @param token_op Token operation type to be assigned
 */
void	create_token(t_data *data, int row, char *word, t_token_op token_op)
{
	load_data(data, row, word, token_op);
}


int	parse_word(t_data *data, int row, char *word)
{
    char		*free_later;
    char		*result;
    t_strinfo	*strinfo;
    int			len;

    (void)data;
    free_later = NULL;
    strinfo = ft_calloc(1, sizeof(t_strinfo));
    len = ft_strlen(word);
    if (ft_strnstr_quotes(word, ">>>", len) || ft_strnstr_quotes(word, "<<<", len))
    {
        free(strinfo);
        return (return_error(WRONG_SYNTAX, " FROM parse_word", data));
    }
    result = find_split(word, strinfo);
    if (!result)
    {
        create_token(data, row, word, UNDEFINED);
        free(strinfo);
        return (OK_SYNTAX);
    }
    while (result)
    {
        if (result[0] != '\0')
        {
            create_token(data, row, result, UNDEFINED);
            // CAMBIO: Liberar result inmediatamente (eval hace copia)
            free(result);
            
            create_token(data, row, strinfo->option_value, UNDEFINED);
            // CAMBIO: Liberar option_value inmediatamente (eval hace copia)
            free(strinfo->option_value);
            strinfo->option_value = NULL;
        }
        else
        {
            create_token(data, row, strinfo->option_value, UNDEFINED);
            // CAMBIO: Liberar option_value inmediatamente
            free(strinfo->option_value);
            strinfo->option_value = NULL;
            
            // CAMBIO: Liberar result aunque esté vacío
            free(result);
        }
        result = find_split(&word[strinfo->next_str_pos], strinfo);
    }
    create_token(data, row, &word[strinfo->next_str_pos], UNDEFINED);
    if (free_later != NULL)
        free(free_later);
    free(strinfo);
    return (0);
}