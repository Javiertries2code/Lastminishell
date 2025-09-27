/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:59:52 by jbravo-           #+#    #+#             */
/*   Updated: 2023/01/10 14:35:59 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*str;
	unsigned int	count;

	count = 0;
	while (s[count])
		count++;
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	count = 0;
	while (s[count])
	{
		str[count] = (char)s[count];
		count++;
	}
	str[count] = '\0';
	return (str);
}
