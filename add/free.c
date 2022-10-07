/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:49:13 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/07 14:52:59 by mdegraeu         ###   ########.fr       */
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

void	ft_free_2D_array(int heigth, int width, int **tab)
{
	(void)width;
	(void)tab;
	int	y;

	y = 0;
	while (y < heigth)
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