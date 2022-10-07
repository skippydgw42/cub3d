/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setparams.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:30:14 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/07 16:05:47 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_linepos(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_char_list(map[i][j]) == 2)
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_colpos(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_char_list(map[i][j]) == 2)
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_length_path(char *str)
{
	int	i;
	int ct;

	i = 0;
	ct = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && (ft_char_list(str[i]) == 2 || str[i] == 'O' || str[i] == 'A'))
		i++;
	while (str[i])
	{
		if (str[i] != 32 && (str[i] < 9 || str[i] > 13))
			ct++;
		i++;
	}
	return (ct);
}

//checkpath texture
char	*ft_get_path(char *str)
{
	int		i;
	int		j;
	char	*dst;
	
	i = 0;
	dst = malloc(sizeof(char) * (ft_length_path(str) + 1));
	if (!dst)
		return (NULL);
	j = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && (ft_char_list(str[i]) == 2 || str[i] == 'O' || str[i] == 'A'))
		i++;
	while (str[i])
	{
		if (str[i] != 32 && (str[i] < 9 || str[i] > 13))
		{
			dst[j] = str[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	free(str);
	return (dst);
}

int	ft_check_path(char *str)
{
	if (access(str, R_OK) == -1)
		return (0);
	return (1);
}

//recuperer les textures des differents points cardinaux dans la struct t_map
char	*ft_chooseparam(t_map *map, char *flat_map, char *str)
{
	str = ft_get_path(str);
	if (flat_map[1])
	{
		if (flat_map[0] == 'N' && flat_map[1] == 'O')
		{
			if (!ft_check_path(str))
				map->no = 0;
			return (map->no_texture = str);
		}
		if (flat_map[0] == 'S' && flat_map[1] == 'O')
		{
			if (!ft_check_path(str))
				map->so = 0;
			return (map->so_texture = str);
		}
		if (flat_map[0] == 'W' && flat_map[1] == 'E')
		{
			if (!ft_check_path(str))
				map->we = 0;
			return (map->we_texture = str);
		}
		if (flat_map[0] == 'E' && flat_map[1] == 'A')
		{
			if (!ft_check_path(str))
				map->ea = 0;
			return (map->ea_texture = str);
		}
	}
	free(str);
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
	if (flat_map[j] && flat_map[j] == '-')
		j++;
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


//set les differents parametres du file dans la structure t_map

int	ft_can_cpy(t_map *map, char *flat_map)
{
	int	i;

	i = 0;
	if (flat_map[i] == 'N' && map->no == 0)
	{
		map->no = 1;
		return (1);
	}
	else if (flat_map[i] == 'S' && map->so == 0)
	{
		map->so = 1;
		return (1);
	} 
	else if (flat_map[i] == 'W' && map->we == 0)
	{
		map->we = 1;
		return (1);
	}
	else if (flat_map[i] == 'E' && map->ea == 0)
	{
		map->ea = 1;
		return (1);
	}
	return (0);
}

void	ft_take_texture(t_map *map, char *flat_map, int x)
{
	int		i;
	char	*str;

	i = 0;
	while (flat_map[i] && i < x)
	{
		while (flat_map[i] == 32 || (flat_map[i] >= 9 && flat_map[i] <= 13))
			i++;
		if (ft_can_cpy(map, &flat_map[i]))
		{
			str = ft_cpyline(&flat_map[i]);
			ft_chooseparam(map, &flat_map[i], str);
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

int	ft_check_rgb_val(int *tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (i < 3)
	{
		if (tab[i] < 0 || tab[i] > 255)
		{
			free (tab);
			return (0);
		}
		i++;
	}
	return (1);
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

int	ft_setparams(t_map *map, char *flat_map)
{
	int	x;

	x = ft_to_map(flat_map, 0);
	ft_take_texture(map, flat_map, x);
	ft_take_rgb_floor(map, flat_map, x);
	ft_take_rgb_ceiling(map, flat_map, x);
	return (1);
}
