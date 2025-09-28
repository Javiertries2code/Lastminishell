#include "../mini.h"

/**
 * @brief Print error message and free all resources before exit
 * 
 * @param data Shell data structure containing all resources
 * @param error_msg Error message to print
 * @return Always returns 1 to indicate error
 */
int	exit_with_error(t_data *data, char *error_msg)
{
	if (error_msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(error_msg, STDERR_FILENO);
	}
	if (data)
		free_all_data(data);
	return (1);
}
/**
 * @brief Safely free string and set pointer to NULL
 * 
 * @param str Pointer to string pointer to free
 */
void	free_str_safe(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

/**
 * @brief Free array of strings safely
 * 
 * @param command Array of strings to free
 */
void	free_commands(char **command)
{
	int	i;

	if (!command)
		return ;
	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}

/**
 * @brief Free linked list of environment variables
 * 
 * @param env_list Head of environment variables list
 */
static void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list->next;
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = temp;
	}
}

/**
 * @brief Free array of token lists safely
 * 
 * @param tokens Array of token list pointers
 */
static void	free_tokens(t_token **tokens)
{
	int		i;
	t_token	*curr;
	t_token	*next;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		curr = tokens[i];
		while (curr)
		{
			next = curr->next;
			free(curr->value);
			free(curr);
			curr = next;
		}
		i++;
	}
	free(tokens);
}

/**
 * @brief Free all allocated memory in data structure safely
 * 
 * @param data Shell data structure to clean up
 */
void	free_all_data(t_data *data)
{
	if (!data)
		return ;
	free_str_safe(&data->str);
	free_commands(data->commands);
	free_env_list(data->env_head);
	free_str_safe(&data->tmp_var_name);
	data->tmp_var_expanded = NULL;
	data->tmp_var_len = 0;
	free_tokens(data->tokens);
	free(data);
}

/**
 * @brief Legacy wrapper for free_str_array (for compatibility)
 * 
 * @param command Array of strings to free
 */
void	free_split(char **command)
{
	free_commands(command);
}
