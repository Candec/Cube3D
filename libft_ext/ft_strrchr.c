/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 19:14:55 by jibanez-          #+#    #+#             */
/*   Updated: 2021/05/03 11:37:31 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (ft_strchr(s, c) == NULL)
		return (NULL);
	i = ft_strlen(s);
	while (s[i] != (char)c && i != 0)
		i--;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return ((char *)s);
}
