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

int	ft_echo(t_token *list)
{
	bool	new_line;

	new_line = true;
	list = list->next;
	if (list && !ft_strcmp("-n", list->value))
	{
		new_line = false;
		list = list->next;
	}
	while (list)
	{
		ft_putstr_fd(list->value, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		list = list->next;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
