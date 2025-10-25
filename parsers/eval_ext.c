/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:12:35 by havr              #+#    #+#             */
/*   Updated: 2025/10/26 00:13:37 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	reassign_value(char **old, char *new)
{
	if (*old && *old != new)
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
