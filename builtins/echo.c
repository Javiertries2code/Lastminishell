/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:39 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:02:45 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

bool	is_n_flag(t_token *list)
{
	size_t	i;

	i = 1;
	while (list->value[i] && list->value[i] == 'n')
		i++;
	if (list->value[i])
		return (false);
	return (true);
}

int	ft_echo(t_token *list)
{
	bool	new_line;

	new_line = true;
	list = list->next;
	while (is_n_flag(list) && !ft_strncmp(list->value, "-", 1))
	{
		list = list->next;
		new_line = false;
	}
	while (list)
	{
		ft_putstr_fd(list->value, STDOUT_FILENO);
		if (new_line)
			ft_putchar_fd(' ', STDOUT_FILENO);
		list = list->next;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/* 
Error with the token that are passed to the stdout
Error with the $? in syntax error
*/