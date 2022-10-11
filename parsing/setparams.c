/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setparams.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:30:14 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 13:01:53 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

char	ft_set_id(char *flat_map, int *i)
{
	char	c;

	*i = 0;
	*i = ft_skipspaces(flat_map);
	c = flat_map[*i];
	*i += 1;
	*i += ft_skipspaces(&flat_map[*i]);
	return (c);
}

//recuperer les textures des differents points cardinaux dans la struct t_map
void	ft_chooseparam(t_map *map, char *flat_map, char *old_path)
{
	int		i;
	char	*path;

	path = strdup(old_path);
	if (ft_set_id(flat_map, &i) == 'N' && flat_map[i] == 'O')
	{
		map->no = 1;
		map->no_texture = path;
	}
	else if (ft_set_id(flat_map, &i) == 'S' && flat_map[i] == 'O')
	{
		map->so = 1;
		map->so_texture = path;
	}
	else if (ft_set_id(flat_map, &i) == 'W' && flat_map[i] == 'E')
	{
		map->we = 1;
		map->we_texture = path;
	}
	else if (ft_set_id(flat_map, &i) == 'E' && flat_map[i] == 'A')
	{
		map->ea = 1;
		map->ea_texture = path;
	}
}

int	ft_setparams(t_map *map, char *flat_map)
{
	int	x;

	x = ft_to_map(flat_map, 0);
	ft_take_texture(map, flat_map, x);
	ft_take_rgb_floor(map, flat_map, x);
	ft_take_rgb_ceiling(map, flat_map, x);
	return (x);
}
