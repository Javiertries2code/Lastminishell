/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:15:03 by havr              #+#    #+#             */
/*   Updated: 2025/10/26 00:15:27 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/**
 * @brief Safely free string
 *
 * @param str String to free
 */
void	free_null(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
		str = NULL;
	}
}

void	free_null_void(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
