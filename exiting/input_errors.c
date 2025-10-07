/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:46:57 by havr              #+#    #+#             */
/*   Updated: 2025/10/06 20:15:18 by havr             ###   ########.fr       */
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
    if (!current)
        return (0);

    print_debug("curent value en red  --");
    // Verificar que current->value no sea NULL antes de usarlo
    if (current->value)
        print_debug(current->value);
    else
        print_debug("(NULL value)");
    print_debug("\n");
    
    i = current->token_op;
    if (current->next)
        j = current->next->token_op;
    // ...existing code...
}