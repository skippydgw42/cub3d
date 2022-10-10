/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:24 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/10 10:36:23 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_mapsize(char *flat_map, int x)
{
	int	i;
	int	ct;
	int	size;

	i = ft_strlen(flat_map) - 1;
	ct = 0;
	size = 0;
	while (i > x && ct < 2)
	{
		if (flat_map[i] == '\n')
		{
			ct++;
			if (ct < 2)
				size++;
		}
		if (flat_map[i] != '\n')
			ct = 0;
		i--;
	}
	if (i <= x)
		size++;
	return (size);
}

int	ft_sublen(char *flat_map)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (flat_map[i] != '\n')
	{
		i--;
		if (flat_map[i] >= 9 && flat_map[i] <= 13)
			ct += 4;
		else
			ct++;
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

void	ft_mapinstruct(t_map *map, char *flat_map, int size)
{
	int	i;
	int	j;
	int	k;

	i = ft_strlen(flat_map);
	map->strmap[size] = 0;
	while (size-- > 0)
	{
		i--;
		j = i;
		while (flat_map[j - 1] != '\n')
			j--;
		map->strmap[size] = malloc(sizeof(char) * (ft_sublen(&flat_map[i]) + 1));
		k = 0;
		while (j <= i)
		{
			if (flat_map[j] >= 9 && flat_map[j] <= 13)
				k += ft_tabcpy(&map->strmap[size][k]);
			else
			{
				map->strmap[size][k] = flat_map[j];
				k++;
			}
			j++;
		}
		map->strmap[size][k] = '\0';
		while (flat_map[i] != '\n')
			i--;
	}
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
	int	size;

	size = ft_mapsize(flat_map, x);
	if (size < 2)
		return (0);
	map->strmap = malloc(sizeof(char*) * (size + 1));
	if (!map->strmap)
		return (0);
	map->width = ft_find_max_length(flat_map, x);
	ft_mapinstruct(map, flat_map, size);
	return (1);
}
