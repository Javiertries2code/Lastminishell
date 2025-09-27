/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:26:37 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/18 21:26:43 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

	char *
	ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = (char *)malloc(1 + ft_strlen(s) * sizeof(char));
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	f(unsigned int i, char c)
{
	char	ch;

	if (i && c != ' ')
		ch = c + 3;
	else
		ch = c;
	return (ch);
}

// int	main(void)
// {
// 	char	*str1;
// 	char	*str2;

// 	str1 = "hola cara bola";
// 	str2 = ft_strmapi(str1, (*f));
// 	printf("\n%s\n", str2);
// 	if (strlen(str1) == strlen(str2))
// 		printf("\n%s\n", "ok");
// 	return (0);
// }
// #include <stdio.h>
