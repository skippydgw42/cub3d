/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:54:05 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/10 17:14:32 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_length_path(char *str)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && (ft_clist(str[i]) == 2 || str[i] == 'O' || str[i] == 'A'))
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
int	ft_check_path(char *str)
{
	if (access(str, R_OK) == -1)
		return (0);
	return (1);
}

//recuperer les textures des differents points cardinaux dans la struct t_map
void	ft_chooseparam(t_map *map, char *flat_map, char *str)
{
	char	*path;

	path = strdup(str);
	if (flat_map[0] == 'N' && flat_map[1] == 'O')
	{
		map->no = 1;
		map->no_texture = path;
	}
	else if (flat_map[0] == 'S' && flat_map[1] == 'O')
	{
		map->so = 1;
		map->so_texture = path;
	}
	else if (flat_map[0] == 'W' && flat_map[1] == 'E')
	{
		map->we = 1;
		map->we_texture = path;
	}
	else if (flat_map[0] == 'E' && flat_map[1] == 'A')
	{
		map->ea = 1;
		map->ea_texture = path;
	}
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
