#include "../mini.h"

/**
 * @brief Searches environment list for a variable name.
 *
 * Sets `data->tmp_var_expanded` if match is found.
 *
 * @param data Pointer to shell data struct.
 */
static void	data_find_in_list(t_data *data)
{
	t_env	*head;

	if (!ft_strcmp(data->tmp_var_name, "?"))
	{
		data->tmp_var_expanded = ft_itoa(sig);
		return ;
	}
	head = data->env_head;
	while (head)
	{
		if (!ft_strcmp(data->tmp_var_name, head->key))
		{
			data->tmp_var_expanded = head->value;
			return ;
		}
		head = head->next;
	}
}

/**
 * @brief Extracts variable name and finds its value in the environment.
 *
 * @param str String starting at '$'.
 * @param quotes Current quote context.
 * @param data Pointer to shell data struct.
 */
void	data_find_var(char *str, int quotes, t_data *data)
{
	(data->tmp_var_name = ft_struntil(&str[1], quotes));
	// str[1 as to avoid the $
	if (data->tmp_var_name == NULL)
		return ;
	data->tmp_var_len = ft_strlen(data->tmp_var_name);
	data_find_in_list(data);
	if (!data->tmp_var_expanded)
	{
		free_null_vars(NULL, data);
	}
}

static void	*cut_substitute(char **prefix, char **suffix, char **str,
		char **tmp, t_data *data)
{
	if (prefix && *prefix)
		free(*prefix);
	if (suffix && *suffix)
		free(*suffix);
	if (tmp && *tmp)
		free(*tmp);
	free_null_vars(*str, data);
	return (NULL);
}

/**
 * @brief Substitutes a variable occurrence in a command string.
 *
 * Builds new string from prefix + expanded value + suffix.
 *
 * @param str Original command string (to free).
 * @param data Pointer to shell data struct.
 * @param quotes Current quote context.
 * @param i Index of '$' in original string.
 * @return New command string with variable expanded.
 */
char	*data_substitute_var(char *str, t_data *data, int i)
{
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*ret;

	prefix = ft_substr(str, 0, i);
	suffix = ft_strdup(&str[i + data->tmp_var_len + 1]);
	if (!prefix || !suffix)
		return (cut_substitute(&prefix, &suffix, &str, NULL, data));
	if (data->tmp_var_expanded)
		tmp = ft_strjoin(prefix, data->tmp_var_expanded);
	else
		tmp = ft_strjoin(prefix, "");
	if (!tmp)
		return (cut_substitute(&prefix, &suffix, &str, NULL, data));
	ret = ft_strjoin(tmp, suffix);
	if (!ret)
		return (cut_substitute(&prefix, &suffix, &str, &tmp, data));
	cut_substitute(&prefix, &suffix, &str, &tmp, data);
	return (ret);
}

/**
 * @brief Expands all environment variables in a command.
 *
 * Handles quote context and replaces variables like $VAR with their values.
 *
 * @param j Index of command in command array.
 * @param data Pointer to shell data struct.
 */
void	expand_var(int j, t_data *data)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = 0;
	while (data->commands[j][i])
	{
		quotes = check_quotes(quotes, data->commands[j][i]);
		if (data->commands[j][i] == '$' && quotes != '\'')
		{
			free_null_vars(NULL, data);
			data->tmp_var_len = ft_var_len(&data->commands[j][i], quotes);
			data_find_var(&data->commands[j][i], quotes, data);
			if (data->tmp_var_expanded)
			{
				data->commands[j] = data_substitute_var(data->commands[j], data,
						i);
				free_null_vars(NULL, data);
				quotes = 0;
				i = -1;
			}
		}
		i++;
	}
}
