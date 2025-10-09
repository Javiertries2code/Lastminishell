/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:46:57 by havr              #+#    #+#             */
/*   Updated: 2025/10/08 20:48:55 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"
/**
 * @brief It returns if the word sent is a redirection
 * 
 * @param word 
 * @param append  flag to evaluate also the heredoc as it could be in and end position,
 * unless there are two in a row.
 * @return int 
 */
int	is_redirection(char *word, int append)
{
	int		i;
	char	**built;
/*
TODO i could pass wordi, word j, and if null and not append, do the thing. 
if i and j are red, but !is_left_right(i, j){
smthg like return(*i == '<' && *i == '>')
};
*/
if (append == ALL)
		built = (char *[]){">", ">>", "<<", "<", NULL};
	else if(append == NO_HEREDOC)
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
	char *i;
	int *j;
	if (!current)
		return (0);

	i = current->value;
	if (current->next == NULL) // is last one, cant be > < >>
	{//
		print("\nCURRENT,\n");
		printf("op\t%d\tvalue\t%s\n\n", current->token_op, current->value);
/////////
		if (is_redirection(i, NO_HEREDOC))
			return (WRONG_SYNTAX);
		
	}
	else
	{//////////
		printf("\nCURRENT\t%s\top%d\n", current->value, current->token_op);
		printf("\t\t\t\tNEXT\t%s\top%d\n\n", current->next->value,
			current->next->token_op);

		// checking two  consecutive redirections
		j = current->next->value;
		// if (is_redirection(i, true) && is_redirection(j, true) && !(*j == '<' && j == '>'))
		// 	return (WRONG_SYNTAX);
		if (is_redirection(i, true) && is_redirection(j, true))
			return (WRONG_SYNTAX);
	}

	return (OK_SYNTAX);
}