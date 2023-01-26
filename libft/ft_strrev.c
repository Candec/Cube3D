/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:40:29 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/28 16:40:29 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s1)
{
	char	swp;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(s1);
	while (++i < len / 2)
	{
		swp = s1[i];
		s1[i] = s1[len - i - 1];
		s1[len - i - 1] = swp;
	}
	return (s1);
}
