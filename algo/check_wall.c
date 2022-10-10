/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:01:52 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/10 15:09:07 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static void	ft_set_ratio_x(t_data *data, t_coord pos)
{
	if (data->orientation == NORTH)
		data->data_tex.ratio_x = fmod(pos.x, 1);
	else if (data->orientation == SOUTH)
		data->data_tex.ratio_x = 1 - fmod(pos.x, 1);
	if (data->orientation == EAST)
		data->data_tex.ratio_x = fmod(pos.y, 1);
	else if (data->orientation == WEST)
		data->data_tex.ratio_x = 1 - fmod(pos.y, 1);
}

static int	ft_sec_value(t_coord coord, t_data *data)
{
	if (coord.x < 0 || coord.y < 0 || coord.x >= data->data_map.width
		|| coord.y >= data->data_map.height)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	ft_cal_x_y(t_coord *coord, t_data *data, int opt)
{
	if (data->angle > M_PI_2 && data->angle < (3 * M_PI_2))
	{
		coord->x *= -1;
		if (opt == VER)
		{
			data->orientation = WEST;
			coord->x--;
		}
	}
	if (data->angle > M_PI && data->angle < 2 * M_PI)
	{
		coord->y *= -1;
		if (opt == HOR)
		{
			data->orientation = NORTH;
			coord->y--;
		}
	}
}

int	ft_check_wall(t_coord coord, t_data *data, int opt)
{
	t_coord	pos;

	pos.x = data->pos.x;
	pos.y = data->pos.y;
	ft_cal_x_y(&coord, data, opt);
	pos.x += coord.x;
	pos.y += coord.y;
	if (ft_sec_value(pos, data))
		return (0);
	ft_set_ratio_x(data, pos);
	return (data->data_map.map[(int)pos.y][(int)pos.x]);
}
