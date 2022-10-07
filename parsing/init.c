/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:55:23 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/07 15:21:37 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

//=====================================================//
//FLAT_MAP set
//=====================================================//

//recupere le file en une chaine de caractere
char	*ft_getflat(int fd)
{
	char	buff[11];
	char	*str;
	char	*tmp;
	int		ret;

	ret = read(fd, buff, 10);
	str = NULL;
	while (ret)
	{
		buff[ret] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buff);
		if (tmp)
			free(tmp);
		ret = read(fd, buff, 10);
	}
	return (str);
}

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
}

int	ft_only_map(char *flat_map)
{
	int	i;
	int	result;

	i = 0;

	while (flat_map[i])
	{
		result = ft_char_list(flat_map[i]);
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
	while (stop == 0)
	{
		while (flat_map[i] == '\n')
			i++;
		x = i;
		stop = 1;
		while (flat_map[i] && flat_map[i] != '\n')
		{
			result = ft_char_list(flat_map[i]);
			if (result != 1 && result != 3)
				stop = 0;
			i++;
			if (!ft_only_map(&flat_map[x]))
				stop = 0;
		}
	}
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
	if (i == 0)
		return (0);
	return (ret);
}

int	ft_init_map(t_map *map, char **av)
{
	int		fd;
	int		x;
	char	*flat_map;

	fd = open(av[1], O_RDONLY);
	if (fd < 1 || fd > 1024)
		return (0); //on return quoi en cas d'erreur qd on peut pas NULL ?
	ft_t_mapstruct(map);
	map->map_name = ft_strdup(av[1]);
	flat_map = ft_getflat(fd);
	if (!flat_map)
		return (0); //same qu'avant
	if (ft_check_flat(flat_map) == 0)
	{
		free (flat_map);
		// ft_freemap(map);
		return (0); //same qu'au dessus
	}
	x = ft_setparams(map, flat_map);
	x = ft_to_map(flat_map, x);
	if (!ft_setmap(map, flat_map, x))
		return (0);
	return (1);
}
