#include "../mini.h"

int	assign_sig(int code)
{
	sig = code;
	return (code);
}

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
		free_all_data(data, assign_sig(sig));
	return (11);
}

int	exit_with_token_error(t_data *data, t_token *tok, char *error_msg)
{
	if (error_msg && tok)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error_msg, STDERR_FILENO);
		ft_putstr_fd(" \'", STDERR_FILENO);
		ft_putstr_fd(tok->value, STDERR_FILENO);
		ft_putendl_fd("`", STDERR_FILENO);
	}
	if (data)
		free_all_data(data, assign_sig(sig));
	return (11);
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
		if(env_list->key)
		{
			free(env_list->key);
			env_list->key = NULL;
		}
		if(env_list->value)
		{
			free(env_list->value);
			env_list->value = NULL;
		}
		free(env_list);
		env_list = temp;
	}
}
/**
 * @brief Free all allocated memory in data structure safely
 * 
 * @param data Shell data structure to clean up
 */
void	free_all_data(t_data *data, int sig)
{
    if (!data)
        return ;
    free_str_safe(&data->str);
    free_split(data->commands);
    free_env_list(data->env_head);
	if (data->env_expr)
		free_env_list(data->env_expr);
    free_str_safe(&data->tmp_var_name);
    data->tmp_var_expanded = NULL;
    data->tmp_var_len = 0;
    free_all_tokens(data);
    if (data->command_set)
        free(data->command_set);
    if (data->l_back)
        free(data->l_back);
    if (data->l_ff)
        free(data->l_ff);
    if (data->l_for)
        free(data->l_for);
    if (data->l_hd)
        free(data->l_hd);
    free(data);
    exit(sig);
}
void	free_split_tripoint(char ***command)
{
	int	i;

	if (!command || !*command)
		return ;
	i = 0;
	while ((*command)[i])
	{
		if ((*command)[i])
		{
			free((*command)[i]);
			(*command)[i] = NULL;
		}
		i++;
	}
	free(*command);
	*command = NULL; 
}
/**
 * @brief Aint sure this is gonna make more problems than helpin, 
 * as a tripple pointer version would do more of a sense
 * 
 * @param command Array of strings to free
 */
void	free_split(char **command)
{
	int	i;

	if (!command)
		return ;
	i = 0;
	while (command[i])
	{
		if (command[i])
		{
			free(command[i]);
			command[i] = NULL;
		}
		i++;
	}
	free(command);
}
