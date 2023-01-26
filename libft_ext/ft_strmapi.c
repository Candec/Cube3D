/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 00:42:59 by jibanez-          #+#    #+#             */
/*   Updated: 2021/02/24 14:38:16 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	unsigned int	i;

	i = 0;
	if (f && s)
	{
		out = malloc((ft_strlen(s)) + 1);
		if (!out)
			return (NULL);
		while (s[i] != '\0')
		{
			out[i] = f(i, s[i]);
			i++;
		}
		out[i] = '\0';
		return (out);
	}
	return (NULL);
}
