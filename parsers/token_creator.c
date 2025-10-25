/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:16:40 by havr              #+#    #+#             */
/*   Updated: 2025/10/26 00:17:38 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/**
 * @brief Handles redirection and builtin evaluation
 */
bool	eval_red_builtin(t_data *data, t_token *token, char *word,
		char *unquoted)
{
	if (check_prev(data, token, word))
	{
		free(unquoted);
		return (true);
	}
	if (eval_red(data, token, word))
	{
		free(unquoted);
		return (true);
	}
	if (eval_builtin(data, token, unquoted))
	{
		token->value = unquoted;
		return (true);
	}
	return (false);
}

/**
 * @brief Evaluates a word and assigns the appropriate token type and value
 */
void	eval(t_data *data, t_token *token, char *word, t_token_op token_op)
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
	if (eval_red_builtin(data, token, word, unquoted_word))
		return ;
	if (is_binary(data, token, unquoted_word))
	{
		token->value = ft_strdup(&unquoted_word[2]);
		free(unquoted_word);
		return ;
	}
	token->value = unquoted_word;
}

/**
 * @brief Handles token creation for empty or operator-only results
 */
static void	handle_token_result(t_data *data, int row, char *result,
		t_strinfo *strinfo)
{
	if (result[0] != '\0')
	{
		create_token(data, row, result, UNDEFINED);
		free(result);
		create_token(data, row, strinfo->option_value, UNDEFINED);
	}
	else
	{
		create_token(data, row, strinfo->option_value, UNDEFINED);
		free(result);
	}
	free(strinfo->option_value);
	strinfo->option_value = NULL;
}

/**
 * @brief Processes word splitting loop
 */
static void	splitter(t_data *data, int row, char *word, t_strinfo *strinfo)
{
	char	*result;

	result = find_split(word, strinfo);
	while (result)
	{
		handle_token_result(data, row, result, strinfo);
		result = find_split(&word[strinfo->next_str_pos], strinfo);
	}
	create_token(data, row, &word[strinfo->next_str_pos], UNDEFINED);
}

int	parse_word(t_data *data, int row, char *word)
{
	char		*result;
	t_strinfo	*strinfo;
	int			len;

	strinfo = ft_calloc(1, sizeof(t_strinfo));
	len = ft_strlen(word);
	if (ft_strnstr_quotes(word, ">>>", len) || ft_strnstr_quotes(word, "<<<",
			len))
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
	splitter(data, row, word, strinfo);
	free(strinfo);
	return (0);
}
