#include "../mini.h"


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