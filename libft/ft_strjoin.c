/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:52:28 by jbravo-           #+#    #+#             */
/*   Updated: 2023/01/10 14:36:15 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static void	new_s(char *str, const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;

	if (!(s1 && s2))
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char)));
	if (!str)
		return (NULL);
	new_s(str, s1, s2);
	return (str);
}
