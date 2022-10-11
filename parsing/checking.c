/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:49:41 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 15:32:31 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_check_extension(char *path, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(path) - 1;
	j = ft_strlen(ext) - 1;
	while (path[i] == ext[j] && (i > 0 && j > 0))
	{
		i--;
		j--;
	}
	if (ft_strlen(path) - i == ft_strlen(ext))
		return (1);
	return (0);
}

int	ft_clist(char c)
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
			if (ft_clist(map[i][j]) == 2)
				player++;
			else if (!ft_clist(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (player != 1)
		return (0);
	return (1);
}

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
			return (0);
		if (map[i][ft_strlen(map[i])] == '0')
			return (0);
		while (map[i][j])
		{
			if (i == 0 && (map[i][j] != '1' && map[i][j] != ' '))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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
