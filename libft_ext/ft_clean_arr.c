/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:09:09 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/27 01:15:04 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clean_arr(char **arr)
{
	size_t	i;

	i = -1;
	if (arr != NULL)
	{
		while (arr[++i] != NULL)
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
}
