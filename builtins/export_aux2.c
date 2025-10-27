/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:10 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 12:58:15 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	free_env_cpy(t_env *nhead)
{
	t_env	*tmp;

	while (nhead)
	{
		tmp = nhead->next;
		free(nhead->key);
		free(nhead->value);
		free(nhead);
		nhead = tmp;
	}
}
