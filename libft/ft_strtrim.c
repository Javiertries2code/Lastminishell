/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:30:47 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/18 21:30:52 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	int				snitch;
	char			*str;
	int				counts1;

	counts1 = 0;
	i = 0;
	str = (char *)malloc((ft_strlen(s1) * sizeof(char)));
	if (!sizeof(str))
		return (NULL);
	while (i < ft_strlen(s1))
	{
		j = 0;
		snitch = 0;
		while (set[j])
		{
			if (s1[i] == set[j++])
				snitch++;
		}
		if (snitch == 0)
			str[counts1++] = s1[i];
		i++;
	}
	return (str);
}

// int main()
// {
// 	char *ptr;
//  char *str1 = "hola cara de bola";
// char *str2 = "ar";
// ptr = ft_strtrim(str1, str2);

// printf("%s\n", ptr);

// return (0);
// }