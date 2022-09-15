/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:55:23 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/15 16:38:48 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

//=====================================================//
//TO DELETE
//=====================================================//
void	ft_printmapstruct(t_map *map)
{
	int	i;

	i = 0;
	printf("%s\n%s\n%s\n%s\n", map->no_texture, map->so_texture, map->we_texture, map->ea_texture);
	printf("floor\n");
	for (int x = 0; x < 3; x++)
		printf("%d ", map->floor[x]);
	printf("\n");
	printf("ceiling\n");
	for (int x = 0; x < 3; x++)
		printf("%d ", map->ceiling[x]);
	printf("\n");
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}
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
//PARAMS set
//=====================================================//

//recuperer les textures des differents points cardinaux dans la struct t_map
char	*ft_chooseparam(t_map *map, char *flat_map, char *str)
{
	if (flat_map[1])
	{
		if (flat_map[0] == 'N' && flat_map[1] == 'O')
			return (map->no_texture = str);
		if (flat_map[0] == 'S' && flat_map[1] == 'O')
			return (map->so_texture = str);
		if (flat_map[0] == 'W' && flat_map[1] == 'E')
			return (map->we_texture = str);
		if (flat_map[0] == 'E' && flat_map[1] == 'A')
			return (map->ea_texture = str);
	}
	return (NULL);
}

//copier une ligne du fichier d'entree
char	*ft_cpyline(char *flat_map)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (flat_map[j] && flat_map[j] != '\n')
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = flat_map[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_preatoi(char *flat_map)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (flat_map[j] && (flat_map[j] >= '0' && flat_map[j] <= '9'))
		j++;
	str = malloc(sizeof(char) * (j - i + 1));
	while (i < j)
	{
		str[i] = flat_map[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

//recupere les valeurs RGB floor && ceiling
void	ft_floor_ceiling(t_map *map, char *flat_map)
{
	int		i;
	int		j;
	char	*str;
	int		*f_or_c;

	i = 0;
	j = 0;
	f_or_c = malloc(sizeof(int) * 3);
	if (flat_map[i] == 'F')
		map->floor = f_or_c;
	else
		map->ceiling = f_or_c;
	while (flat_map[i] && flat_map[i] != '\n' && j < 3)
	{
		while (flat_map[i] && (flat_map[i] < '0' || flat_map[i] > '9'))
			i++;
		str = ft_preatoi(&flat_map[i]);
		f_or_c[j] = ft_atoi(str);
		free(str);
		j++;
		while (flat_map[i])
		{
			if (flat_map[i] < '0' || flat_map[i] > '9')
				break ;
			i++;
		}
	}
}

//set les differents parametres du file dans la structure t_map
int	ft_setparams(t_map *map, char *flat_map)
{
	int		i;
	int		ct;
	char	*str;

	i = 0;
	ct = 0;
	while (ct < 6 && flat_map[i])
	{
		while (flat_map[i] == '\n' || flat_map[i] == ' ')
			i++;
		if (flat_map[i] == 'N' || flat_map[i] == 'S' || flat_map[i] == 'W' || flat_map[i] == 'E')
		{
			str = ft_cpyline(&flat_map[i]);
			ft_chooseparam(map, &flat_map[i], str);
			ct++;
		}
		else if (flat_map[i] == 'F' || flat_map[i] == 'C')
		{
			ft_floor_ceiling(map, &flat_map[i]);
			ct++;
		}
		while (flat_map[i] != '\n')
			i++;
	}
	return (i);
}
//=====================================================//
//MAP set
//=====================================================//

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
			size++;
			ct++;
		}
		if (flat_map[i] != '\n')
			ct = 0;
		i--;
	}
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
	while (size >= 0)
	{
		i--;
		j = i;
		while (flat_map[j - 1] != '\n')
			j--;
		map->map[size] = malloc(sizeof(char) * (ft_sublen(&flat_map[i]) + 1));
		map->map[size][ft_sublen(&flat_map[i]) + 1] = '\0';
		k = 0;
		while (j <= i)
		{
			if (flat_map[j] >= 9 && flat_map[j] <= 13)
				k += ft_tabcpy(&map->map[size][k]);
			else
			{
				map->map[size][k] = flat_map[j];
				k++;
			}
			j++;
		}
		map->map[size][k] = '\0';
		while (flat_map[i] != '\n')
			i--;
		size--;
	}
}

int	ft_setmap(t_map *map, char *flat_map, int x)
{
	int	size;

	size = ft_mapsize(flat_map, x);
	map->map = malloc(sizeof(char*) * (size+ 1));
	if (!map->map)
		return (0);
	map->map[size + 1] = 0;
	ft_mapinstruct(map, flat_map, size);
	return (1);
}

//=====================================================//
//STRUCT set
//=====================================================//
t_map	*ft_init_map(int fd)
{
	int		x;
	t_map	*map;
	char	*flat_map;

	if (fd < 1 || fd > 1024)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	flat_map = ft_getflat(fd);
	if (!flat_map)
		return (NULL);
	x = ft_setparams(map, flat_map);
	while (flat_map[x] && flat_map[x] == '\n')
		x++;
	ft_setmap(map, flat_map, x);
	ft_printmapstruct(map);
	return (map);
}
/*
int	check_extension(char *map_name)
{
	if (!.cub)
		return (0);
	return (1);
}

int	check_char(char **map)
{
	if (!0 1 N S E W)
		return (0);
	return (1);
}

int	check_closed(char **map)
{
	return (1);
}

int	check_description_pose()
{
	return (1);
}

int	parsing(t_map map)
{
	check_extension(map->map_name);
	check_char(map->map);
	check_closed(map->map);
	return (1);
}
*/