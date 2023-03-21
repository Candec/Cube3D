/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:56:21 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/21 18:37:20 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_add_str_to_arr(char *str, char ***arr)
{
	int		i;
	int		j;
	char	**new_arr;
	char	*n_str;

	i = 0;
	j = -1;
	n_str = ft_malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!n_str)
		return (1);
	ft_strcpy(n_str, str);
	while (*arr && arr[0][i])
		i++;
	new_arr = ft_malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (1);
	while (++j < i)
		new_arr[j] = ft_strdup(arr[0][j]);
	new_arr[i] = n_str;
	new_arr[i + 1] = NULL;
	if (*arr)
		ft_clean_arr(*arr);
	*arr = new_arr;
	return (0);
}
