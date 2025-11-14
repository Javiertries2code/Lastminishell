/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:02 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:03:01 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_pwd(void)
{
	char	*work_dir;

	work_dir = NULL;
	work_dir = getcwd(NULL, 0);
	if (!work_dir)
		return (-1);
	ft_putstr_fd(work_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(work_dir);
	return (assign_sig(0));
}
