#include "../mini.h"

void	reassign_value(char **old, char *new)
{
	if (*old && *old != new) // Only free if different pointer
	{
		free(*old);
	}
	*old = new;
}

bool	check_prev(t_data *data, t_token *token, char *word)
{
	int	i;

	(void)data;
	if (!token->prev)
	{
		return (false);
	}
	i = token->prev->token_op;
	if (i >= 1 && i <= 4)
	{
		token->token_op = STRING;
		reassign_value(&token->value, remove_outer_quotes(word));
		return (true);
	}
	return (false);
}

int	eval_red(t_data *data, t_token *token, char *word)
{
	if (!ft_strncmp(word, ">>", 2))
	{
		data->l_ff[token->row] = token->pos;
		token->token_op = APPEND;
		token->value = ft_strdup(word); // CAMBIO: Hacer copia
		return (true);
	}
	else if (!ft_strncmp(word, "<<", 2))
	{
		data->l_hd[token->row] = token->pos;
		token->token_op = HEREDOC;
		token->value = ft_strdup(word); // CAMBIO: Hacer copia
		return (true);
	}
	else if (!ft_strncmp(word, ">", 1))
	{
		data->l_for[token->row] = token->pos;
		token->token_op = RED_FORWD;
		token->value = ft_strdup(word); // CAMBIO: Hacer copia
		return (true);
	}
	else if (!ft_strncmp(word, "<", 1))
	{
		data->l_back[token->row] = token->pos;
		token->token_op = RED_BACKWD;
		token->value = ft_strdup(word); // CAMBIO: Hacer copia
		return (true);
	}
	return (false);
}

/**
 * @brief Compares two strings lexicographically.
 *

	* This function compares the string pointed to by s1 to the string pointed to by s2.
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
	if (ft_strncmp("./", word, 2))
	{
		if ( word[2] != 0 && ft_isalnum(word[2]))
		{
			token->token_op = BINARY;
			token->value = word;
			data->command_set[token->row] = true;
			return (true);
		}
		else
			return false;
	}
	return false;
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
			// printf("GOT BUILT IN %s\n", word);
			token->token_op = BUILTIN;
			token->value = word;
			data->command_set[token->row] = true;
			return (true);
		}
		i++;
	}
	return (false);
}
// __attribute__((unused))  bool	eval_command(t_data *data, t_token *token,
//	char *word)
// {

// 	if (data->command_set[token->row] == true)
// 		return (true);

// 	if (get_cmd_path(data->env_head, word))
// 	{
// 		token->token_op = COMMAND;
// 		data->command_set[token->row] = true;
// 	}
// 	// by now
// 	return (data->command_set);
// }
