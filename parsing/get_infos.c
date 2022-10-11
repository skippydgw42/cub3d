/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:56:58 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 12:08:40 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

//set les differents parametres du file dans la structure t_map
int	ft_can_cpy(t_map *map, char *flat_map)
{
	if (flat_map[0] == 'N' && map->no == 0)
		return (1);
	else if (flat_map[0] == 'S' && map->so == 0)
		return (1);
	else if (flat_map[0] == 'W' && map->we == 0)
		return (1);
	else if (flat_map[0] == 'E' && map->ea == 0)
		return (1);
	return (0);
}

void	ft_take_texture(t_map *map, char *flat_map, int x)
{
	int		i;
	char	*str;
	char	*path;

	i = 0;
	while (flat_map[i] && i < x)
	{
		while (flat_map[i] == 32 || (flat_map[i] >= 9 && flat_map[i] <= 13))
			i++;
		if (ft_can_cpy(map, &flat_map[i]))
		{
			str = ft_cpyline(&flat_map[i]);
			path = ft_get_path(str);
			if (ft_check_path(path) && flat_map[i + 1])
				ft_chooseparam(map, &flat_map[i], path);
			free(path);
			while (flat_map[i] && flat_map[i] != '\n')
				i++;
		}
		i++;
	}
}

//recupere les valeurs RGB floor && ceiling
int	*ft_floor_ceiling(char *flat_map)
{
	int		i;
	int		j;
	char	*str;
	int		*f_or_c;

	i = 0;
	j = 0;
	f_or_c = malloc(sizeof(int) * 3);
	while (flat_map[i] && flat_map[i] != '\n' && j < 3)
	{
		while (flat_map[i] && (flat_map[i] < '0' || flat_map[i] > '9'))
		{
			if (flat_map[i] == '-')
				break ;
			i++;
		}
		str = ft_preatoi(&flat_map[i]);
		f_or_c[j] = ft_atoi(str);
		free(str);
		j++;
		while (flat_map[i] && (flat_map[i] >= '0' && flat_map[i] <= '9'))
			i++;
	}
	return (f_or_c);
}

void	ft_take_rgb_floor(t_map *map, char *flat_map, int x)
{
	int	i;

	i = 0;
	while (flat_map[i] && i < x)
	{
		if (flat_map[i] == 'F' && map->no < 2)
		{
			map->floor = ft_floor_ceiling(&flat_map[i]);
			if (ft_check_rgb_val(map->floor))
				map->no = 2;
			else
				map->floor = NULL;
		}
		i++;
	}
}

void	ft_take_rgb_ceiling(t_map *map, char *flat_map, int x)
{
	int	i;

	i = 0;
	while (flat_map[i] && i < x)
	{
		if (flat_map[i] == 'C' && map->so < 2)
		{
			map->ceiling = ft_floor_ceiling(&flat_map[i]);
			if (ft_check_rgb_val(map->ceiling))
				map->so = 2;
			else
				map->ceiling = NULL;
		}
		i++;
	}
}
