/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:15:53 by havr              #+#    #+#             */
/*   Updated: 2025/10/26 00:16:02 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	handle_strinfo(char *s, t_strinfo *strinfo)
{
	if (s[0] && s[1] && s[1] == s[0])
	{
		strinfo->advance = 2;
	}
	strinfo->next_str_pos = strinfo->next_str_pos + strinfo->pos
		+ strinfo->advance;
	strinfo->option_value = ft_substr((const char *)s, 0, strinfo->advance);
}
