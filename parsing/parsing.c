/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:11:49 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/07 15:52:35 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_check_extension(char *map_name)
{
	int	i;

	i = ft_strlen(map_name) - 1;
	if (map_name[i] == 'b')
		i--;
	if (map_name[i] == 'u')
		i--;
	if (map_name[i] == 'c')
		i--;
	if (map_name[i] == '.')
		i--;
	if (ft_strlen(map_name) - i == 5)
		return (1);
	return (0);
}

int	ft_char_list(char c)
{
	if (c == '1' || c == '0') 
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (2);
	if (c == ' ' || (c >= 9 && c <= 13))
		return (3);
	return (0);
}

int	ft_check_char(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_char_list(map[i][j]) == 2)
				player++;
			else if (!ft_char_list(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (player != 1)
		return (0);
	return (1);
}

//CHECK CLOSE MAP

int	ft_check_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] == '0')
			return (2);
		if (map[i][ft_strlen(map[i])] == '0')
			return (2);
		while (map[i][j])
		{
			if (i == 0 && (map[i][j] != '1' && map[i][j] != ' '))
				return (0);
			j++;
		}
		i++;
	}
	return  (1);
}

//SUFFISANT POUR VERIF MAP CLOSE ?
int	ft_around(char **map, int i, int j)
{
	int	result;
	if (j == 0 || i == 0)
		return (0);
	else if (!map[i][j + 1])
		return (0);
	else if (!map[i + 1])
		return (0);
	result = ft_char_list(map[i][j + 1]);
	if (result != 1 && result != 2)
		return (0);
	result = ft_char_list(map[i][j - 1]);
	if (result != 1 && result != 2)
		return (0);
	result = ft_char_list(map[i + 1][j]);
	if (result != 1 && result != 2)
		return (0);
	result = ft_char_list(map[i - 1][j]);
	if (result != 1 && result != 2)
		return (0);
	return (1);
}

int	ft_coord_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!ft_around(map, i, j))
				{
					printf("%d %d\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_struct(t_map *map)
{
	if (!map->no_texture || !map->so_texture)
		return (0);
	if (!map->we_texture || !map->ea_texture)
		return (0);
	if (!map->floor || !map->ceiling)
		return (0);
	if (!map->strmap)
		return (0);
	return (1);
}

int	ft_parsing(t_data *data)
{
	if (!ft_check_struct(&data->data_map))
		return (ft_return("struct"));
	if (!ft_check_extension(data->data_map.map_name))
		return (ft_return("extension"));
	if (!ft_check_char(data->data_map.strmap))
		return (ft_return("char"));
	if (!ft_check_closed(data->data_map.strmap))
		return (ft_return("close"));
	if (!ft_coord_check(data->data_map.strmap))
		return (ft_return("coord"));
	ft_imap(&data->data_map);
	return (1);
}