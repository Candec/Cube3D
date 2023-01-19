/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:46:57 by jibanez-          #+#    #+#             */
/*   Updated: 2021/02/24 11:48:23 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*d;
	void	*s;

	d = dest;
	s = (void *)src;
	if (dest < src && dest + n >= src)
	{
		while (n--)
			*(char *)d++ = *(char *)src++;
	}
	else if (src < dest && src + n > dest)
	{
		s += n;
		d += n;
		while (n--)
			*(char *)--d = *(char *)--s;
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
