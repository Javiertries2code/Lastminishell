/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:53:26 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/18 21:16:15 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (s[0] != '\0')
	{
		write(fd, &s[0], 1);
		s++;
	}
	write(fd, "\n", 1);
}
// int main(void)
// {
//     ft_putendl_fd("hello", 1);
//     return (0);
// }