/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:45:17 by jbravo-           #+#    #+#             */
/*   Updated: 2023/01/04 12:46:52 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	while_func(size_t n, unsigned char *aux, unsigned char *dst)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
			dst[i] = aux[i];
			i++;
	}	
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*aux;
	unsigned char	*dst;

	dst = (unsigned char *)dest;
	aux = (unsigned char *)src;
	if ((dest < src))
		while_func(n, aux, dst);
	if ((dest > src))
	{
		while (n)
		{
			dst[n - 1] = aux[n - 1];
			n--;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	size_t	len;
	char	dst[];
	char	dst_[];

   	const char 	src[] = "test basic"; 
    dst[] = "123456789123456789";
    const char	src_[] = "test basic"; 
    dst_[] = "123456789123456789";
	len = 4;
	printf("\nSize: %lu\n", len);
	printf("No cambiado: %p\n", dst);
	ft_memmove(dst, &dst[4], len);
	printf("Cambiado: %p\n\n", dst);
	printf("Original No cambiado: %p\n", dst_);
	memmove(dst_, &dst[4], len);
	printf("Original Cambiado: %p\n\n", dst_);	
}
*/