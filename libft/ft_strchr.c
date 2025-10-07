/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:21:06 by jbravo            #+#    #+#             */
/*   Updated: 2025/10/06 00:16:32 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Searches for the first occurrence of character c in string s
 * Returns pointer to the first occurrence, or NULL if not found
 * Also returns pointer to null terminator if c is '\0' */
char	*ft_strchr(const char *s, int c)
{
	unsigned int	len;

	len = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((char)c == '\0')
		return ((char *)&s[len]);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
