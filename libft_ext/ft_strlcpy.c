/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:18:29 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/27 01:17:03 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src)
		return (0);
	if (dstsize)
	{
		i = -1;
		while (++i < dstsize && src[i])
			dst[i] = src[i];
		if (i == dstsize)
			i--;
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
