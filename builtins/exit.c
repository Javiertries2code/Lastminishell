/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:32 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:02:23 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_exit(t_token *list, t_data *data)
{
	int	sig;

	sig = ft_atoi(list->next->value);
	free_all_data(data, assign_sig(sig));
	return (0);
}
