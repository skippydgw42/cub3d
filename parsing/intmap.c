/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:26:54 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/12 11:51:51 by ltrinchi         ###   ########lyon.fr   */
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

void	ft_imap(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		return ;
	while (map->strmap[i])
	{
		map->map[i] = malloc(sizeof(char) * (map->width));
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
