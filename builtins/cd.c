/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:42 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:03:10 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	go_home_path(void)
{
	char	*path = "/home/minishell";

	if (path && chdir(path) == 0)
	{
		return (0);
	}
	else
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (1);
}

static int	go_old_path(void)
{
	char	*path = "/home/minishell";

	if (path && chdir(path) == 0)
	{
		return (0);
	}
	else
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (1);
}

int	ft_cd(t_token *list)
{
	list = list->next;
	if (!list)
	{
		return (go_home_path());
	}
	else
	{
		if (!strcmp("~"	, list->value))
			return (go_home_path());
		else if (!strcmp("-", list->value))
			return (go_old_path());
		else if (chdir(list->value) == 0)
			return (0);
	}
	return (1);
}
