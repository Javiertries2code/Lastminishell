/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:46:57 by havr              #+#    #+#             */
/*   Updated: 2025/09/28 16:51:29 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/**
 * check_pipes_reds - Validates pipe and redirection operator syntax
 * @current: Pointer to the current token in the token list
 *
 * This function checks for syntax errors in pipe and redirection operators:
 * - Validates that redirection operators are not followed by other operators
 * - Ensures pipes are not at the beginning or end of command sequences
 * - Checks that redirection operators have valid following tokens
 *
 * Return: 1 if syntax error is found, 0 if syntax is valid
 */
int	check_pipes_reds(t_token *current)
{
	int i;
	int j;
	print_debug("check reds ");
	print_debug(current->value );
	
	i = current->token_op;
	if (current->next)
	{	
		print_debug("check reds ");
		print_debug(current->next->value );

		j = current->next->token_op;
		if (i > RED_FORWD && i < HEREDOC)
			if ((j > RED_FORWD && j < HEREDOC) || *current->value == '|')
				return (1);
	}
	if ((!current->prev || !current->next) && *current->value == '|')
		return (1);
	if (!current->next && ft_strchr("<>", *current->value))
		return (1);

	return (0);
}