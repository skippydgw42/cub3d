/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:55:23 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 10:17:24 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

//=====================================================//
//STRUCT set
//=====================================================//
void	ft_t_mapstruct(t_map *map)
{
	map->we_texture = NULL;
	map->we = 0;
	map->no_texture = NULL;
	map->no = 0;
	map->ea_texture = NULL;
	map->ea = 0;
	map->so_texture = NULL;
	map->so = 0;
	map->floor = NULL;
	map->ceiling = NULL;
	map->strmap = NULL;
	map->map = NULL;
	map->map_name = NULL;
	map->height = 0;
	map->width = 0;
	map->map = NULL;
}

int	ft_only_map(char *flat_map)
{
	int	i;
	int	result;

	i = 0;
	while (flat_map[i])
	{
		result = ft_clist(flat_map[i]);
		if (flat_map[i] != '\n')
			if (result == 0)
				return (0);
		i++;
	}
	return (1);
}

int	ft_to_map(char *flat_map, int x)
{
	int	i;
	int	stop;
	int	result;

	i = x;
	stop = 0;
	while (flat_map[i] && stop == 0)
	{
		while (flat_map[i] == '\n')
			i++;
		x = i;
		stop = 1;
		while (flat_map[i] && flat_map[i] != '\n')
		{
			result = ft_clist(flat_map[i]);
			if (result != 1 && result != 3)
				stop = 0;
			i++;
			if (!ft_only_map(&flat_map[x]))
				stop = 0;
		}
	}
	if ((size_t)i == ft_strlen(flat_map))
		return (i);
	return (x);
}

int	ft_check_flat(char *flat_map)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (flat_map[i])
	{
		if (flat_map[i] != '\n' && flat_map[i] != ' ')
			ret = 1;
		i++;
	}
	if (i == 0 || ret == 0)
	{
		free(flat_map);
		return (0);
	}
	return (ret);
}

int	ft_init_map(t_map *map, char **av)
{
	int		fd;
	int		x;
	char	*flat_map;

	fd = open(av[1], O_RDONLY);
	if (fd < 1 || fd > 1024)
		return (0);
	ft_t_mapstruct(map);
	flat_map = ft_getflat(fd);
	if (!flat_map)
		return (0);
	if (!ft_check_flat(flat_map))
		return (0);
	map->map_name = ft_strdup(av[1]);
	x = ft_setparams(map, flat_map);
	if ((size_t)x == ft_strlen(flat_map))
	{
		free(flat_map);
		ft_free_texture_path(map);
		return (0);
	}
	if (!ft_setmap(map, flat_map, x))
		return (ft_free_init(map, flat_map));
	free(flat_map);
	return (1);
}
