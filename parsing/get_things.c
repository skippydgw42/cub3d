/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:47:45 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/10 17:08:17 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

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

int	ft_mapsize(char *flat_map, int x)
{
	int	ct;

	ct = 0;
	while (flat_map[x])
	{
		while (flat_map[x] && flat_map[x] == '\n')
			x++;
		if (flat_map[x])
			ct++;
		while (flat_map[x] && flat_map[x] != '\n')
			x++;
	}
	return (ct);
}

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
	while (str[i] && (ft_clist(str[i]) == 2 || str[i] == 'O' || str[i] == 'A'))
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
			if (ft_clist(map[i][j]) == 2)
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
			if (ft_clist(map[i][j]) == 2)
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}
