/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:05:14 by havr              #+#    #+#             */
/*   Updated: 2025/11/09 23:55:06 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * @brief replaces token value by "<>" and its operator by RED_B_F,
	and skips next token.
 *
 * @param token
 */
void	replace_value(t_token *token)
{
	t_token	*current;

	current = token;
	free_null(&current->value);
	current->value = ft_strdup("<>");
	current->token_op = RED_B_F;
	skip_token(current);
}
