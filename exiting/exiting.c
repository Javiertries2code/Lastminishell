/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:03:17 by havr              #+#    #+#             */
/*   Updated: 2025/11/15 15:04:03 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	assign_sig(int code)
{
	g_sig = code;
	return (code);
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
		if (env_list->key)
		{
			free(env_list->key);
			env_list->key = NULL;
		}
		if (env_list->value)
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
