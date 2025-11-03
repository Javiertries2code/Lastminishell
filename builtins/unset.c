/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:06 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:02:16 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_unset(t_token *list, t_data *data)
{
	list = list->next;
	while (list && list->token_op == STRING)
	{
		remove_by_key(&data->env_head, list->value);
		list = list->next;
	}
	return (0);
}
