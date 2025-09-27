/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:31:17 by jbravo            #+#    #+#             */
/*   Updated: 2023/01/10 14:37:54 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (len > (ft_strlen(s) - start + 1))
		len = (ft_strlen(s) - start + 1);
	if (s[0] == '\0' || !len || start > ft_strlen(s))
		return ((char *)ft_strdup(""));
	str = (char *)malloc(len + 1 * sizeof(char));
	if (!str || !s)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
