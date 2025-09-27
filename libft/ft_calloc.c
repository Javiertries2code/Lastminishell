/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:06:47 by jbravo            #+#    #+#             */
/*   Updated: 2025/09/27 18:01:43 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if (!size || size)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	ft_bzero(ptr, size);

	return (ptr);
}