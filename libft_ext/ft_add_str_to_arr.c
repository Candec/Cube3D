/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:56:21 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/15 15:32:37 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_add_str_to_arr(char *str, char **arr)
// {
// 	int		i;
// 	int		j;
// 	char	**new_arr;
// 	char	*n_str;

// 	i = 0;
// 	n_str = malloc(sizeof(char) * ft_strlen(str));
// 	ft_strcpy(n_str, str, 0, ft_strlen(str));
// 	while (arr && arr[i])
// 		i++;
// 	new_arr = malloc(sizeof(char *) * (i + 2));
// 	if (!new_arr)
// 		return (1);
// 	j = 0;
// 	while (arr && (j < i))
// 	{
// 		new_arr[j] = (arr[j]);
// 		j++;
// 	}
// 	new_arr[i] = n_str;
// 	new_arr[i + 1] = NULL;
// 	if (arr)
// 		ft_clean_arr(arr);
// 	arr = new_arr;
// 	return (0);
// }

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
	ft_strcpy(n_str, str, 0, ft_strlen(str));
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