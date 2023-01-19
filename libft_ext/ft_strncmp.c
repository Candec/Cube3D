/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 19:27:24 by jibanez-          #+#    #+#             */
/*   Updated: 2021/05/03 11:38:27 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (1)
	{
		if (*s1 != *s2++)
		{
			--s2;
			if (*s1 < 0 || *s2 < 0)
				return ((unsigned char)(*s1 - *s2));
			return (*s1 - *s2);
		}
		if (*s1++ == 0)
			break ;
		if (--n == 0)
			break ;
	}
	return (0);
}
