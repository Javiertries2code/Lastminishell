/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:27:49 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/18 21:30:08 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (little[0] == '\0')
		return ((char *)&big[0]);
	while (i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j])
			{
				if (little[j + 1] == '\0')
				{
					return ((char *)&big[i]);
				}
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// // int main()
// // {
// // 	unsigned int len;
// // 	len = 40;
// // char *text= "How to find a needle in a haystack,
// while
// n characters evaluated ";
// 	// char *needle= "needle";
// 	// printf("\n%c\n", (ft_strnstr(text, needle, len)[0]));
// 	// return(0);
// 	// }#include<string.h>
