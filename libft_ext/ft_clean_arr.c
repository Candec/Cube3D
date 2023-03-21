/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:09:09 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/21 20:34:45 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clean_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
			ft_free(arr[i++]);
	}
	ft_free(arr);
	arr = NULL;
}
