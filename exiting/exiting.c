 #include "../mini.h"

/**
 * @brief Frees a specific number of strings
 * 
 * @param strs Array of strings to free
 * @param count Number of strings to free
 */


/**
 * @brief Frees a linked list of environment variables.
 *
 * @param env Pointer to the first element of the list.
 */
static void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

/**
 * @brief Frees an array of strings.
 *
 * @param arr Array of dynamically allocated strings.
 */
void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Frees an array of token lists.
 *
 * Each element of the array is a linked list of t_token.
 *
 * @param tokens Array of token pointers.
 */
static void	free_tokens(t_token **tokens)
{
	int		i;
	t_token	*tmp;
	t_token	*next;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		tmp = tokens[i];
		while (tmp)
		{
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		i++;
	}
	free(tokens);
}

/**
 * @brief Frees all data inside the t_data structure.
 *
 * Frees: input string, commands, expanded vars,
 * environment list, temporary vars and tokens.
 *
 * @param data Pointer to t_data structure to clean.
 */
void	free_data(t_data *data)
{
	if (!data)
		return ;
	free(data->str);
	free_split(data->commands);
	//free_split(data->expanded);
	free_env_list(data->env_head);
	free(data->tmp_var_name);
	data->tmp_var_name = NULL;
	data->tmp_var_expanded = NULL;
	data->tmp_var_len = 0;
	free_tokens(data->tokens);
	free(data);
}
