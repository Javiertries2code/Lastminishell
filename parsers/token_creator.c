/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:16:40 by havr              #+#    #+#             */
/*   Updated: 2025/11/11 14:48:30 by havr             ###   ########.fr       */
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
int	cut_eval(char **str)
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

int	parse_word(t_data *data, int row, char *word)
{
	char		*result;
	t_strinfo	*strinfo;

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
