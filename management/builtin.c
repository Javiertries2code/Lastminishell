/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:04:52 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:04:56 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	builtin_manager(t_token *list, t_data *data)
{
	if (!ft_strcmp(list->value, "echo"))
		return (ft_echo(list));
	if (!ft_strcmp(list->value, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(list->value, "env"))
		return (ft_env(data));
	if (!ft_strcmp(list->value, "unset"))
		return (ft_unset(list, data));
	if (!ft_strcmp(list->value, "cd"))
		return (ft_cd(list));
	if (!ft_strcmp(list->value, "export"))
		return (ft_export(list, data));
	if (!ft_strcmp(list->value, "exit"))
		return (ft_exit(list, data));
	return (0);
}
