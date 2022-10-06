/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:09:40 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/06 16:46:11 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int		ft_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return ((red * 256 * 256) + (green * 256) + blue);
}

void	ft_draw_wall_xpm(t_data *data, t_img_mlx *src_img, t_coord screen, double ratio)
{
	my_mlx_pixel_put(&data->data_mlx.img, screen.x, screen.y, my_mlx_pixel_get_color(src_img, data->data_tex.start * src_img->width, (screen.y - data->data_tex.verti_shift) * ratio));
}

void ft_draw_wall(t_data *data, double length, int pos, int dir)
{
	t_coord	screen;

	data->data_tex.height = HEIGHT_WINDOW / length;
	data->data_tex.verti_shift = (HEIGHT_WINDOW - data->data_tex.height) / 2;
	screen.x = (pos * WIDTH_WINDOW) / (FOV * RESOLUTION);
	while (screen.x < ((pos + 1) * (WIDTH_WINDOW / (FOV * RESOLUTION))))
	{
		screen.y = data->data_tex.verti_shift;
		if (screen.y < 0)
			screen.y = 0;
		while (screen.y < data->data_tex.height + data->data_tex.verti_shift)
		{
			if (dir == NORTH)
				ft_draw_wall_xpm(data, &data->data_tex.NO, screen, data->data_tex.SO.height / data->data_tex.height);
			else if (dir == EAST)
				ft_draw_wall_xpm(data, &data->data_tex.EA, screen, data->data_tex.WE.height / data->data_tex.height);
			else if (dir == WEST)
				ft_draw_wall_xpm(data, &data->data_tex.WE, screen, data->data_tex.EA.height / data->data_tex.height);
			else if (dir == SOUTH)
				ft_draw_wall_xpm(data, &data->data_tex.SO, screen, data->data_tex.NO.height / data->data_tex.height);
			screen.y++;
			if (screen.y > HEIGHT_WINDOW)
				break;
		}
		screen.x++;
	}
}

void ft_draw_ceiling(t_data *data, int color)
{
	int x;
	int y;

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

void ft_draw_floor(t_data *data, int color)
{
	int x;
	int y;

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
