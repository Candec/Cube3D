/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 19:21:01 by jibanez-          #+#    #+#             */
/*   Updated: 2021/05/03 11:37:53 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *a, const char *b, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*b == '\0' || b == NULL)
		return ((char *)a);
	while (a[i] != '\0' && i < len)
	{
		j = 0;
		while (b[j] == a[i + j] && i + j < len)
		{
			if (b[j + 1] == '\0')
			{
				return ((char *)a + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
