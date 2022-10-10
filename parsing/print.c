/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:04:02 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/10 10:29:14 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

//=====================================================//
//TO DELETE
//=====================================================//
void	ft_printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	ft_printmapstruct(t_map map)
{
	int	i;

	i = 0;
	printf("=================\n");
	printf("%s\n", map.map_name);
	printf("=================\n");
	printf("%s\n%s\n%s\n%s\n", map.no_texture, map.so_texture, map.we_texture, map.ea_texture);
	printf("\n======\n");
	printf("FLOOR\n");
	for (int x = 0; x < 3; x++)
	{
		printf("%d ", map.floor[x]);
	}
	printf("\n======\n");
	printf("CEILING\n");
	for (int x = 0; x < 3; x++)
	{
		printf("%d ", map.ceiling[x]);
	}
	printf("\n======\nMAP\n");
	ft_printmap(map.strmap);
	printf("\n======\nINT_MAP\n");
	printf("height:%d | max length:%d\n", map.height, map.width);
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.width; j++)
		{
			printf("%d", map.map[i][j]);
		}
		printf("\n");
	}
}