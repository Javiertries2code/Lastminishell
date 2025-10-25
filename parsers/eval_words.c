/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:13:53 by havr              #+#    #+#             */
/*   Updated: 2025/10/26 00:14:54 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	eval_red(t_data *data, t_token *token, char *word)
{
	if (!ft_strncmp(word, ">>", 2))
	{
		data->l_ff[token->row] = token->pos;
		token->token_op = APPEND;
	}
	else if (!ft_strncmp(word, "<<", 2))
	{
		data->l_hd[token->row] = token->pos;
		token->token_op = HEREDOC;
	}
	else if (!ft_strncmp(word, ">", 1))
	{
		data->l_for[token->row] = token->pos;
		token->token_op = RED_FORWD;
	}
	else if (!ft_strncmp(word, "<", 1))
	{
		data->l_back[token->row] = token->pos;
		token->token_op = RED_BACKWD;
	}
	else
		return (false);
	token->value = ft_strdup(word);
	return (true);
}

/**
 * @brief Compares two strings lexicographically.
 *

	* This function compares the string pointed to
	 by s1 to the string pointed to by s2.
 * The comparison is done using unsigned characters,
	so that '\200' is greater than '\0'.
 *
 * @param s1 Pointer to the first null-terminated string to be compared
 * @param s2 Pointer to the second null-terminated string to be compared
 *
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or to be greater than s2.
 *         - < 0: s1 is lexicographically less than s2
 *         - = 0: s1 is lexicographically equal to s2
 *         - > 0: s1 is lexicographically greater than s2
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool	is_binary(t_data *data, t_token *token, char *word)
{
	if (!ft_strncmp("./", word, 2))
	{
		if (word[2] != 0 && ft_isalnum(word[2]))
		{
			token->token_op = BINARY;
			token->value = word;
			data->command_set[token->row] = true;
			return (true);
		}
		else
			return (false);
	}
	return (false);
}

bool	eval_builtin(t_data *data, t_token *token, char *word)
{
	char	**built;
	int		i;

	if (token->prev && (token->prev->token_op >= 1
			&& token->prev->token_op <= 4))
		return (false);
	if (data->command_set[token->row] == true)
		return (false);
	built = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit",
		NULL};
	i = 0;
	while (built[i])
	{
		if (ft_strcmp(word, built[i]) == 0)
		{
			token->token_op = BUILTIN;
			token->value = word;
			data->command_set[token->row] = true;
			return (true);
		}
		i++;
	}
	return (false);
}
