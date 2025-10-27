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

int	ft_cd(t_token *list)
{
	char	*path;

	list = list->next;
	if (!list)
	{
		path = getenv("HOME");
		if (path && chdir(path) == 0)
			return (0);
	}
	else
	{
		if (chdir(list->value) == 0)
			return (0);
	}
	return (1);
}
