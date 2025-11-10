/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:16:40 by havr              #+#    #+#             */
/*   Updated: 2025/11/09 23:38:10 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/**
 * @brief Evaluates a word and assigns the appropriate token type and value
 * @param data Main data structure containing all parsing information
 * @param token Token structure to be filled with evaluation results
 * @param word Input word to be evaluated
 * @param token_op Token operation type (currently unused)
 */
static int	cut_eval(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

/**
 * @brief Evaluates a word and assigns the appropriate token type and value
 * @param data Main data structure containing all parsing information
 * @param token Token structure to be filled with evaluation results
 * @param word Input word to be evaluated
 * @param token_op Token operation type (currently unused)
 */
int	eval(t_data *data, t_token *token, char *word)
{
	char	*unquoted_word;
	char	*tmp;

	tmp = remove_outer_quotes(word);
	unquoted_word = ft_strdup(tmp);
	free(tmp);
	if (word[0] == '\0')
		return (cut_eval(&unquoted_word));
	if (check_prev(data, token, word))
		return (cut_eval(&unquoted_word));
	if (eval_red(data, token, word))
		return (cut_eval(&unquoted_word));
	if (eval_builtin(data, token, unquoted_word))
	{
		token->value = unquoted_word;
		return (0);
	}
	if (is_binary(data, token, unquoted_word))
	{
		token->value = ft_strdup(&unquoted_word[2]);
		return (cut_eval(&unquoted_word));
	}
	token->value = unquoted_word;
	return (0);
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
	eval(data, new_token, word);
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

static void	free_result_option(char **result, char **option_value)
{
	if (result && *result)
	{
		free(*result);
		*result = NULL;
	}
	if (option_value && *option_value)
	{
		free(*option_value);
		*option_value = NULL;
	}
}

static int	parse_init(t_data *data, char *word, t_strinfo **strinfo,
		char **result)
{
	int	len;

	*strinfo = ft_calloc(1, sizeof(t_strinfo));
	if (!*strinfo)
		return (return_error(WRONG_SYNTAX, " parse_word: malloc fail", data));
	len = ft_strlen(word);
	if (ft_strnstr_quotes(word, ">>>", len) || ft_strnstr_quotes(word, "<<<",
			len))
	{
		data->error_red = ft_strdup(word);
		free(*strinfo);
		return (return_error(WRONG_SYNTAX, NULL, data));
	}
	*result = find_split(word, *strinfo);
	return (OK_SYNTAX);
}

static void	split_result(t_data *data, int row, char *result,
		t_strinfo *strinfo)
{
	if (result[0] != '\0')
	{
		create_token(data, row, result, UNDEFINED);
		free(result);
		create_token(data, row, strinfo->option_value, UNDEFINED);
		free(strinfo->option_value);
		strinfo->option_value = NULL;
	}
	else
	{
		free(result);
		create_token(data, row, strinfo->option_value, UNDEFINED);
		free(strinfo->option_value);
		strinfo->option_value = NULL;
	}
}

int	parse_word(t_data *data, int row, char *word)
{
	char *result;
	t_strinfo *strinfo;

	if (parse_init(data, word, &strinfo, &result) != OK_SYNTAX)
		return (return_error(WRONG_SYNTAX, NULL, data));
	if (!result)
	{
		create_token(data, row, word, UNDEFINED);
		free(strinfo);
		return (OK_SYNTAX);
	}
	while (result)
	{
		split_result(data, row, result, strinfo);
		result = find_split(&word[strinfo->next_str_pos], strinfo);
	}
	create_token(data, row, &word[strinfo->next_str_pos], UNDEFINED);
	free(strinfo);
	return (OK_SYNTAX);
}