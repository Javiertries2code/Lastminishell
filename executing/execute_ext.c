/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 23:46:50 by havr              #+#    #+#             */
/*   Updated: 2025/10/25 23:49:37 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	build_data_info(t_data *data)
{
	data->command_set = ft_calloc(data->num_comands, sizeof(int));
	data->l_back = ft_calloc(data->num_comands, sizeof(int));
	data->l_ff = ft_calloc(data->num_comands, sizeof(int));
	data->l_for = ft_calloc(data->num_comands, sizeof(int));
	data->l_hd = ft_calloc(data->num_comands, sizeof(int));
	build_list_heads(data);
}

/**
 * @brief builds the first element of the token list, as
 * to have where to start
 *
 * @param data
 */
void	build_list_heads(t_data *data)
{
	int	i;

	i = 0;
	data->tokens = ft_calloc(data->num_comands + 1, sizeof(t_token *));
	while (i < data->num_comands)
	{
		data->tokens[i] = new_empty_token();
		data->tokens[i]->row = i;
		i++;
	}
	data->tokens[i] = NULL;
}

t_token	*new_empty_token(void)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	new_token->token_op = UNDEFINED;
	return (new_token);
}
