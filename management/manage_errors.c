/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:04:05 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 17:32:15 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	token_with_error(char *error_msg, char *value)
{
	if (error_msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error_msg, STDERR_FILENO);
		ft_putstr_fd(" `", STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
	}
	return (assign_sig(2));
}

int	token_with_no_path(char *value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(value);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (assign_sig(2));
}
