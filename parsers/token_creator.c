#include "../mini.h"

/**
 * @brief it will evaluate in order pending to make the eval command
 *
 * @param data
 * @param token
 * @param word
 * @param token_op
 */
static void	eval(t_data *data, t_token *token, char *word, t_token_op token_op)
{
	char	*unquoted_word;
	char	*tmp;

	(void)token_op;
	// case i am losing the pointer
	tmp = remove_outer_quotes(word);
	unquoted_word = ft_strdup(tmp);
	//
	// token->token_op = STRING;
	token->value = unquoted_word;
	//
	printf(" word to eval %s\n", word);
	printf(" word to evalunqutoted %s\n", unquoted_word);
	if (word[0] == '\0')
		return ;
	if (check_prev(data, token, word))
		return ;
	printf(" AFTER CHECK PREV word to eval %s\n", word);
	printf("  AFTER CHECK PREV word to evalunqutoted %s\n", unquoted_word);
	if (eval_red(data, token, word))
		return ;
	printf(" AFTER CHECK RED word to eval %s\n", word);
	printf("  AFTER CHECK RED word to evalunqutoted %s\n", unquoted_word);
	if (eval_builtin(data, token, unquoted_word))
	{
		printf(" AFTER CHECK BUILIN word to eval %s\n", word);
		printf("  AFTER CHECK BUILIN word to evalunqutoted %s\n",
			unquoted_word);
		token->value = unquoted_word; // Agregar esta línea
		return ;
	}
	printf("AFTER ALLunqueoted word to eval %s\n", word);
	printf("AFTER ALLword to eval AFTER %s\n", unquoted_word);
}

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

void	load_data(t_data *data, int row, char *word, t_token_op token_op)
{
	t_token	*new_token;

	if (remove_outer_quotes(word)[0] == '\0')
		return ;
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

void	create_token(t_data *data, int row, char *word, t_token_op token_op)
{
	// t_token	*new_token;
	//	printf("CREATE TOKEN row%d  :%s  op:%d\n \n", row, word, token_op);
	load_data(data, row, word, token_op);
}

/**
 * @brief This one goes recursevely finding redirecition not between quotes,
	and splitting
 *
 * @param data
 * @param row
 * @param word
 * @return int
 */
int	parse_word(t_data *data, int row, char *word)
{
	(void)data;
	char *free_later = NULL;
	t_strinfo *strinfo = ft_calloc(1, sizeof(t_strinfo));

	int len = ft_strlen(word);
	if (ft_strnstr_quotes(word, ">>>", len) || ft_strnstr_quotes(word, "<<<",
			len))
		return (exiting(data,"ERROR, pendin hadle"));

	char *result = find_split(word, strinfo);

	if (!result)
	{
		create_token(data, row, word, UNDEFINED);
		return (0);
	}

	while (result)
	{
		if (result[0] != '\0')
		{
			create_token(data, row, result, UNDEFINED);
			create_token(data, row, strinfo->option_value, UNDEFINED);
		}
		else
		{
			create_token(data, row, strinfo->option_value, UNDEFINED);
		}
		if (result)
			result = find_split(&word[strinfo->next_str_pos], strinfo);
	}
	if (result)
		printf("SALIDA  value :%s\n \n", result);
	if (strinfo->option_value)
		printf("SALIDA RED::%s\n", strinfo->option_value);

	create_token(data, row, &word[strinfo->next_str_pos], UNDEFINED);

	if (free_later != NULL)
		free(free_later);

	return (0);
}