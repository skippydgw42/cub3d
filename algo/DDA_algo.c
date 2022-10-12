/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:50:09 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/12 09:42:13 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static double	ft_shift(t_data *data, int opt)
{
	double	tmp;
	double	pos;

	tmp = 0;
	if (opt == HOR)
		pos = data->pos.y;
	if (opt == VER)
		pos = data->pos.x;
	while (tmp < pos)
		tmp++;
	if ((opt == VER && (data->angle > M_PI_2 && data->angle < (3 * M_PI_2)))
		|| (opt == HOR && (data->angle > M_PI && data->angle < 2 * M_PI)))
		return (1 - (tmp - pos));
	return (tmp - pos);
}

static double	ft_horiz(t_data *data)
{
	double	length;
	t_coord	coord;

	length = ft_shift(data, HOR);
	while (1)
	{
		data->orientation = SOUTH;
		coord.x = fabs(length / tan(data->angle));
		coord.y = fabs(length);
		if (ft_check_wall(coord, data, HOR))
			break ;
		length++;
		if (fabs(length) > data->data_map.height)
			break ;
	}
	return (fabs(length / sin(data->angle)));
}

static double	ft_verti(t_data *data)
{
	double	length;
	t_coord	coord;

	length = ft_shift(data, VER);
	while (1)
	{
		data->orientation = EAST;
		coord.x = fabs(length);
		coord.y = fabs(length * tan(data->angle));
		if (ft_check_wall(coord, data, VER))
			break ;
		length++;
		if (fabs(length) > data->data_map.width)
			break ;
	}
	return (fabs(length / cos(data->angle)));
}

double	ft_length(t_data *data)
{
	double	length_hor;
	double	length_ver;
	int		ver_or;
	double	start_ver;

	length_ver = ft_verti(data);
	ver_or = data->orientation;
	start_ver = data->data_tex.ratio_x;
	length_hor = ft_horiz(data);
	if (length_hor < length_ver)
		return (length_hor);
	data->data_tex.ratio_x = start_ver;
	data->orientation = ver_or;
	return (length_ver);
}
