/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:59:55 by jibanez-          #+#    #+#             */
/*   Updated: 2021/05/10 19:01:40 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	arr[12];
	int		i;
	int		sign;

	ft_memset(arr, 0, 12);
	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	sign = ft_ispositive(n);
	n = ft_abs(n);
	while (n > 0)
	{
		arr[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (sign < 0)
		arr[i] = '-';
	ft_strrev(arr);
	return (ft_strdup(arr));
}
