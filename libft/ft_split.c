/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:15 by jbravo-           #+#    #+#             */
/*   Updated: 2023/01/03 20:42:21 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter(const char *s, char c)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (counter);
}

static char	*new_str(const char *s, char c)
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	ptr = (char **)ft_calloc(counter(s, c) + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != c)
		{
			ptr[i++] = new_str(&(s[j]), c);
			while (s[j] && s[j] != c)
				j++;
		}
		else
			j++;
	}
	return (ptr);
}
