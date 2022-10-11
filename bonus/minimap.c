/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:05:12 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/11 15:09:56 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static void	ft_draw_square(t_data *data, t_coord coord, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < SIZE_CUBE)
	{
		y = 0;
		while (y < SIZE_CUBE)
		{
			my_mlx_pixel_put(&data->data_mlx.img, (x + coord.x * SIZE_CUBE), (y
					+ coord.y * SIZE_CUBE), color);
			y++;
		}
		x++;
	}
}

static void	ft_draw_wall_map(t_data *data, int color)
{
	t_coord	coord;

	coord.x = fmod(data->pos.x, 1) * -1;
	while (coord.x <= SIZE_MINI_MAP)
	{
		coord.y = fmod(data->pos.y, 1) * -1;
		while (coord.y <= SIZE_MINI_MAP)
		{
			if (ft_check_map(data, coord.x + data->pos.x - (SIZE_MINI_MAP / 2),
					coord.y + data->pos.y - (SIZE_MINI_MAP / 2)) == 1)
				ft_draw_square(data, coord, color);
			coord.y++;
		}
		coord.x++;
	}
}

static void	ft_draw_frame(t_data *data, int color)
{
	t_coord	coord;

	coord.x = 0;
	while (coord.x < SIZE_CUBE * (SIZE_MINI_MAP + 1))
	{
		coord.y = 0;
		while (coord.y < SIZE_CUBE)
		{
			my_mlx_pixel_put(&data->data_mlx.img, coord.x, coord.y, color);
			my_mlx_pixel_put(&data->data_mlx.img, coord.x, (SIZE_CUBE
					* (SIZE_MINI_MAP + 1)) - coord.y - 1, color);
			my_mlx_pixel_put(&data->data_mlx.img, (SIZE_CUBE * (SIZE_MINI_MAP
						+ 1)) - coord.y - 1, coord.x, color);
			my_mlx_pixel_put(&data->data_mlx.img, coord.y, coord.x, color);
			coord.y++;
		}
		coord.x++;
	}
}

static void	ft_draw_floor_map(t_data *data, int color)
{
	t_coord	coord;

	coord.x = 0;
	while (coord.x < SIZE_MINI_MAP * SIZE_CUBE)
	{
		coord.y = 0;
		while (coord.y < SIZE_MINI_MAP * SIZE_CUBE)
		{
			my_mlx_pixel_put(&data->data_mlx.img, coord.x, coord.y, color);
			coord.y++;
		}
		coord.x++;
	}
}

void	ft_draw_map(t_data *data)
{
	ft_draw_floor_map(data, 0);
	ft_draw_fov(data, ft_rgb(222, 0, 0));
	ft_draw_wall_map(data, ft_rgb(255, 255, 255));
	ft_draw_frame(data, ft_rgb(125, 125, 125));
}
