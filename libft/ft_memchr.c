/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:08:26 by jbravo            #+#    #+#             */
/*   Updated: 2023/01/10 14:34:56 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	ch;

	str = (char *)s;
	ch = (char)c;
	while (n--)
	{
		if (ch == *str)
		{
			return ((void *)str);
		}
		str++;
	}
	return (NULL);
}
