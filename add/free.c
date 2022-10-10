/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:49:13 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/10 11:42:33 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

void	ft_freedstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_array(int size, int **tab)
{
	int	y;

	y = 0;
	while (y < size)
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}

// void	ft_freemap(t_map map)
// {
// 	free(map.map_name);
// 	if (map.map)
// 		ft_freedstr(map.map);
// 	if (map.floor)
// 		free(map.floor);
// 	if (map.ceiling)
// 	free(map.ceiling);
// 	if (map)
// 	free(map);
// }
