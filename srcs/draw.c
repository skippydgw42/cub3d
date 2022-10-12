/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:09:40 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/12 10:23:25 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static void	ft_draw_wall_xpm(t_data *data, t_img_mlx *src_img, t_coord screen,
		double ratio_y)
{
	my_mlx_pixel_put(&data->data_mlx.img, screen.x, screen.y,
		my_mlx_pixel_get_color(src_img, data->data_tex.ratio_x
			* src_img->width, (screen.y - data->data_tex.verti_shift)
			* ratio_y));
}

void	ft_choose_tex(t_data *data, t_coord screen, int dir)
{
	if (dir == NORTH)
		ft_draw_wall_xpm(data, &data->data_tex.no, screen,
			data->data_tex.so.height / data->data_tex.height);
	else if (dir == EAST)
		ft_draw_wall_xpm(data, &data->data_tex.ea, screen,
			data->data_tex.we.height / data->data_tex.height);
	else if (dir == WEST)
		ft_draw_wall_xpm(data, &data->data_tex.we, screen,
			data->data_tex.ea.height / data->data_tex.height);
	else if (dir == SOUTH)
		ft_draw_wall_xpm(data, &data->data_tex.so, screen,
			data->data_tex.no.height / data->data_tex.height);
}

void	ft_draw_wall(t_data *data, double length, int pos, int dir)
{
	t_coord	screen;

	data->data_tex.height = HEIGHT_WINDOW / length;
	data->data_tex.verti_shift = (HEIGHT_WINDOW - data->data_tex.height) / 2;
	screen.x = (pos * WIDTH_WINDOW) / (FOV * RESOLUTION);
	while (screen.x < ((pos + 1) * (WIDTH_WINDOW / (FOV * RESOLUTION))))
	{
		screen.y = (int)data->data_tex.verti_shift;
		if (screen.y < 0)
			screen.y = 0;
		while (screen.y <= data->data_tex.height + data->data_tex.verti_shift)
		{
			ft_choose_tex(data, screen, dir);
			screen.y++;
			if (screen.y == HEIGHT_WINDOW)
				break ;
		}
		screen.x++;
		if (screen.x == WIDTH_WINDOW)
			break ;
	}
}

void	ft_draw_ceiling(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH_WINDOW)
	{
		y = 0;
		while (y < HEIGHT_WINDOW / 2)
		{
			my_mlx_pixel_put(&data->data_mlx.img, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_draw_floor(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH_WINDOW)
	{
		y = HEIGHT_WINDOW / 2;
		while (y < HEIGHT_WINDOW)
		{
			my_mlx_pixel_put(&data->data_mlx.img, x, y, color);
			y++;
		}
		x++;
	}
}
