/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 20:40:23 by jbravo-           #+#    #+#             */
/*   Updated: 2023/01/10 21:38:44 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(const char *s1, char const *set, int i, int signal)
{
	if (signal == 0)
	{
		while (ft_strchr(set, (int)s1[i]))
			i++;
	}
	if (signal == 1)
	{
		while (ft_strrchr(set, (int)s1[i - 1]))
			i--;
	}
	return (i);
}

static char	*new_str(int i, int j, char *str, const char *s1 )
{
	int		len;

	len = (int)ft_strlen(s1);
	if (!str)
		return (NULL);
	ft_memcpy((void *)str, (void *)&s1[i], (len - i - (len - j)));
	str[len - i - (len - j)] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	if (*s1 == '\0')
	{
		str = (char *)malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	j = (int)ft_strlen(s1);
	len = j;
	i = 0;
	i = counter(s1, set, i, 0);
	j = counter(s1, set, j, 1);
	if ((len - i - (len - j)) <= 0 || len == 0)
		return (ft_strdup(""));
	else
	{
		str = (char *)malloc(len - i - (len - j) + 1);
		return ((char *)new_str(i, j, str, s1));
	}
}
