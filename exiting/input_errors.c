/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:46:57 by havr              #+#    #+#             */
/*   Updated: 2025/11/11 19:21:49 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/**
 * @brief It returns if the word sent is a redirection
 * AMAZING, THIS SHOUD BE FAILING AS I AM PASSING true, while ALL is 0..
 *
 * @param word

	* @param append  flag to evaluate also the heredoc as
	it could be in and end position,
 * unless there are two in a row.
 * @return int
 */
int	is_redirection(char *word, int append)
{
	int		i;
	char	**built;

	if (append == ALL)
		built = (char *[]){">", ">>", "<<", "<", NULL};
	else if (append == NO_HEREDOC)
		built = (char *[]){">", ">>", "<", NULL};
	i = 0;
	while (built[i])
	{
		if (ft_strcmp(word, built[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief if current == "<" and next == ">" returns 1
 *
 */
static int	__attribute__((unused))	excp(char *current, char *next)
{
	if (!ft_strcmp(current, "<") && !ft_strcmp(next, ">"))
		return (RED_EXCP);
	else
		return (0);
}

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
	char	*i;
	char	*j;

	if (!current)
		return (0);
	i = current->value;
	if (current->next == NULL)
	{
		if (is_redirection(i, NO_HEREDOC))
			return (WRONG_SYNTAX);
	}
	else
	{
		j = current->next->value;
		if (is_redirection(i, ALL) && is_redirection(j, ALL))
		{
			if (excp(i, j) == RED_EXCP && current->next->next != NULL
				&& is_redirection(current->next->next->value, ALL) == 0)
				return (RED_EXCP);
			else
				return (WRONG_SYNTAX);
		}
	}
	return (OK_SYNTAX);
}
