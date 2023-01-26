/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 23:17:46 by jibanez-          #+#    #+#             */
/*   Updated: 2021/01/12 11:02:39 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	len = ft_strlen(&s1[i]);
	if (len != 0)
		while (s1[i + len - 1] && ft_strchr(set, s1[i + len - 1]) != NULL)
			len--;
	return (ft_substr(s1, i, len));
}
