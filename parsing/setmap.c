/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:24 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 10:10:19 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_sublen(char *flat_map)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (flat_map[i] != '\n')
	{
		if (flat_map[i] >= 9 && flat_map[i] <= 13)
			ct += 4;
		else
			ct++;
		i++;
	}
	return (ct);
}

int	ft_tabcpy(char *dst)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		dst[i] = ' ';
		i++;
	}
	return (4);
}

void	ft_mapinstruct(t_map *map, char *flat_map, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		map->strmap[i] = malloc(sizeof(char) * (ft_sublen(&flat_map[x]) + 1));
		j = 0;
		while (flat_map[x] != '\n')
		{
			if (flat_map[x] >= 9 && flat_map[x] <= 13)
				j += ft_tabcpy(&map->strmap[i][j]);
			else
			{
				map->strmap[i][j] = flat_map[x];
				j++;
			}
			x++;
		}
		map->strmap[i][j] = '\0';
		// REVIEW C'est ici le SegV
		while (flat_map[x] == '\n')
			x++;
		// 
		i++;
	}
	map->strmap[i] = 0;
}

int	ft_find_max_length(char *flat_map, int x)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (flat_map[x])
	{
		if (flat_map[x] == '\n')
		{
			if (cp < i)
				cp = i;
			i = 0;
		}
		else if (flat_map[x] >= 9 && flat_map[x] <= 13)
			i += 4;
		else
			i++;
		x++;
	}
	return (cp);
}

int	ft_setmap(t_map *map, char *flat_map, int x)
{
	map->height = ft_mapsize(flat_map, x);
	if (map->height < 2)
		return (0);
	map->strmap = malloc(sizeof(char *) * (map->height + 1));
	if (!map->strmap)
		return (0);
	map->width = ft_find_max_length(flat_map, x);
	ft_mapinstruct(map, flat_map, x);
	return (1);
}
