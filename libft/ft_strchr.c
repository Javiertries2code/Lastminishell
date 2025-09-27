/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:21:06 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/18 21:21:29 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] || s[i - 1])
	{
		if (c == s[i])
			return (&s[i]);
		i++;
	}
	return (&s[i]);
}

// int	main(void)
// {
// 	char ch = '\n';
// 	printf("%c\n", *ft_strchr("hobla carabola", ch));
// 	printf("%c\n", *(ft_strchr("hola carabola", ch) + 1));
// }