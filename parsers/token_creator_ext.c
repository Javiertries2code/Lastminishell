/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:16:57 by havr              #+#    #+#             */
/*   Updated: 2025/11/11 14:47:38 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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

void	free_result_option(char **result, char **option_value)
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

int	parse_init(t_data *data, char *word, t_strinfo **strinfo, char **result)
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

void	split_result(t_data *data, int row, char *result, t_strinfo *strinfo)
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
