/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:26:54 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/10 10:36:53 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_countline(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_convert(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (1);
	return (0);
}

// void	ft_countlength(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	map->width = 0;
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (map->map[i][j] != -1)
// 			j++;
// 		if (i > 0)
// 			if (j > map->width)
// 				map->width = j;
// 		i++;
// 	}
// }

void	ft_imap(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->height = ft_countline(map->strmap);
	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
		return ;
	while (map->strmap[i])
	{
		map->map[i] = malloc(sizeof(int) * (map->width));
		if (!map->map[i])
			return ;
		j = 0;
		while (map->strmap[i][j])
		{
			map->map[i][j] = ft_convert(map->strmap[i][j]);
			j++;
		}
		while (j < map->width)
		{
			map->map[i][j] = 0;
			j++;
		}
		i++;
	}
}