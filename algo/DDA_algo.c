/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:50:09 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/05 17:10:07 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

// REVIEW Bug avec la collision quand je suis sur un coordonnee parfaite (ex: x=2, y=3)
int	ft_check_wall(double x, double y, t_data *data, int opt)
{
	double	pos_x = data->pos.x;
	double	pos_y = data->pos.y;

	if (x < 0 || y < 0 || x > data->data_map.width || y > data->data_map.height)
		return (0);
	if (data->angle > M_PI_2 && data->angle < (3 * M_PI_2))
	{
		x *= -1;
		if (opt == VER)
		{
			data->orientation = WEST;
			x--;
		}
	}
	if (data->angle > M_PI && data->angle < 2 * M_PI)
	{
		y *= -1;
		if (opt == HOR)
		{
			data->orientation = NORTH;
			y--;
		}
	}
	pos_x += x;
	pos_y += y;
	if (pos_x < 0 || pos_y < 0 || pos_x > data->data_map.width || pos_y > data->data_map.height)
		return (0);
	if (data->orientation == NORTH)
		data->data_tex.start = fmod(pos_x, 1);
	else if(data->orientation == SOUTH)
		data->data_tex.start = 1 - fmod(pos_x, 1);

	if (data->orientation == EAST)
		data->data_tex.start = fmod(pos_y, 1);
	else if (data->orientation == WEST)
		data->data_tex.start = 1 - fmod(pos_y, 1);

	return (data->data_map.map[(int)pos_y][(int)pos_x]);
}

static double ft_shift(t_data *data, int opt)
{
	double tmp;
	double pos;

	tmp = 0;

	if (opt == HOR)
		pos = data->pos.y;
	if (opt == VER)
		pos = data->pos.x;
	while (tmp < pos)
		tmp++;
	if ((opt == VER && (data->angle > M_PI_2 && data->angle < (3 * M_PI_2))) ||
		(opt == HOR && (data->angle > M_PI && data->angle < 2 * M_PI)))
		return (1 - (tmp - pos));
	return (tmp - pos);
}

static double ft_horiz(t_data *data)
{
	double length;
	double x;
	double y;

	length = ft_shift(data, HOR);
	while (1)
	{
		data->orientation = SOUTH;
		x = fabs(length / tan(data->angle));
		y = fabs(length);
		if (ft_check_wall(x, y, data, HOR))
			break;
		length++;
		if (fabs(length) > data->data_map.width + 2)
			break;
	}
	return (fabs(length / sin(data->angle)));
}

static double ft_verti(t_data *data)
{
	double length;
	double x;
	double y;

	length = ft_shift(data, VER);
	while (1)
	{
		data->orientation = EAST;
		x = fabs(length);
		y = fabs(length * tan(data->angle));
		if (ft_check_wall(x, y, data, VER))
			break;
		length++;
		if (fabs(length) > data->data_map.height + 2)
			break;
	}
	return (fabs(length / cos(data->angle)));
}

double ft_length(t_data *data)
{
	double length_hor;
	double length_ver;
	int ver_or;
	double start_ver;

	length_ver = ft_verti(data);
	ver_or = data->orientation;
	start_ver = data->data_tex.start;
	length_hor = ft_horiz(data);
	if (length_hor < length_ver)
		return (length_hor);
	data->data_tex.start = start_ver;
	data->orientation = ver_or;
	return (length_ver);
}
