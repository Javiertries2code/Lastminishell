/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 23:46:38 by havr              #+#    #+#             */
/*   Updated: 2025/11/06 00:09:31 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/**
 * @brief Adds a new token to the end of the linked list
 *
 * @param data
 * @param new
 */
static void	add_token_to_list(t_data *data,
		t_token *new)
{
	int		row;
	t_token	*current;

	row = new->row;
	if (data->tokens[row] == NULL)
	{
		data->tokens[row] = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		current = data->tokens[row];
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
}

/**
 * @brief Gets the whole line of command,
	splits in each every word respecting quotes, and send the  word
 * add_token() to be evaluated
 *
 * @param data
 * @param i
 */
static void	get_tokens(t_data *data, int j)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split_quotes(data->commands[j], ' ');
	while (words[i] != NULL)
	{
		parse_word(data, j, words[i]);
		i++;
	}
	free_split(words);
}

/**
 * @brief
 *
 * @param data
 * @param row
 */
void	free_token_list(t_data *data, int row)
{
	t_token	*current;
	t_token	*next;

	if (!data || !data->tokens || row >= data->num_comands)
		return ;
	current = data->tokens[row];
	while (current)
	{
		next = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	data->tokens[row] = NULL;
}

/**
 * @brief frees all token lists in data
 *
 * @param data
 */
void	free_all_tokens(t_data *data)
{
	int	i;

	if (!data || !data->tokens)
		return ;
	i = 0;
	while (i < data->num_comands)
	{
		free_token_list(data, i);
		i++;
	}
	free(data->tokens);
	data->tokens = NULL;
}

static void	skip_token(t_token *token)
{
    t_token	*tmp;

    tmp = token->next;
    token->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = token;
    if (tmp->value)
        free(tmp->value);
    free(tmp);
}

static void	clear_repeated_env(t_data *data, int i)
{
    t_token	*tmp;

    tmp = data->tokens[i];
    if (!tmp || ft_strcmp("env", tmp->value))
        return ;
    while (tmp->next && !ft_strcmp("env", tmp->next->value))
        skip_token(tmp);
}
/**
 * @brief
 * creates the heads, and for every lone of commands,
	calls get tokens to load the list
 *
 * @param data
 */
void	tokenize(t_data *data)
{
	int	i;

	i = 0;
	build_data_info(data);
	while (i < data->num_comands)
	{
		get_tokens(data, i);
		clear_repeated_env(data, i);
		i++;
	}
	
}
