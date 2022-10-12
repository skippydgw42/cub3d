/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:49:13 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/12 11:48:45 by ltrinchi         ###   ########lyon.fr   */
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

void	ft_free_texture_path(t_map *map)
{
	free(map->map_name);
	free(map->floor);
	free(map->ceiling);
	free(map->no_texture);
	free(map->so_texture);
	free(map->ea_texture);
	free(map->we_texture);
}

int	ft_free_init(t_map *map, char *flat_map)
{
	int	i;

	if (flat_map)
		free(flat_map);
	ft_free_texture_path(map);
	i = 0;
	if (map->strmap)
	{
		while (map->strmap[i])
		{
			free(map->strmap[i]);
			i++;
		}
		free(map->strmap);
	}
	return (0);
}

void	ft_free_array(int size, char **tab)
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

int	ft_freemap(t_map *map)
{
	ft_free_texture_path(map);
	ft_freedstr(map->strmap);
	return (0);
}
