/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:22:43 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/06 19:26:47ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

// NOTE Dessiner un bloc de la map
void ft_draw_square(t_data *data, int pos_x, int pos_y, int color, int size)
{
	int x;
	int y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			my_mlx_pixel_put(&data->data_mlx.img, x + pos_x, y + pos_y, color);
			y++;
		}
		x++;
	}
}

int	ft_check_map(t_data *data, int x, int y)
{
	if (x <= 0 || y <= 0)
		return (1);
	if (x >= data->data_map.width || y >= data->data_map.height)
		return (1);
	return (data->data_map.map[y][x]);
}

void	ft_draw_wall_map(t_data *data)
{
	double x;
	double y;

	double shift_x;
	double	shift_y;

	x = 0;
	shift_x = fmod(data->pos.x, 1);
	shift_y = fmod(data->pos.y, 1);
	while (x <= SIZE_MINI_MAP)
	{
		y = 0;
		while (y <= SIZE_MINI_MAP)
		{
			if (ft_check_map(data, x + data->pos.x - (SIZE_MINI_MAP / 2), y + data->pos.y - (SIZE_MINI_MAP / 2)))
				ft_draw_square(data, (x - shift_x) * SIZE_CUBE, (y - shift_y) * SIZE_CUBE, 0xffffff, SIZE_CUBE - 1);
			y++;
		}
		x++;
	}
}

void	ft_draw_frame(t_data *data, int color)
{
	int i;

	i = 0;
	while (i <= SIZE_MINI_MAP)
	{
		ft_draw_square(data, i * SIZE_CUBE, 0, color, SIZE_CUBE);
		ft_draw_square(data, i * SIZE_CUBE, SIZE_MINI_MAP * SIZE_CUBE, color, SIZE_CUBE);
		ft_draw_square(data, 0, i * SIZE_CUBE, color, SIZE_CUBE);
		ft_draw_square(data, SIZE_MINI_MAP * SIZE_CUBE, i * SIZE_CUBE, color, SIZE_CUBE);
		i++;
	}
}

void	ft_draw_floor_map(t_data *data)
{
	int	x;
	int y;

	x = 0;
	while (x < SIZE_MINI_MAP)
	{
		y = 0;
		while (y < SIZE_MINI_MAP)
		{
			ft_draw_square(data, x * SIZE_CUBE, y * SIZE_CUBE, 0x0, SIZE_CUBE);
			y++;
		}
		x++;

	}
}

void ft_draw_map(t_data *data)
{
	ft_draw_floor_map(data);
	ft_draw_lines(data);
	ft_draw_wall_map(data);
	ft_draw_frame(data, ft_rgb(125, 125, 125));
}

// NOTE Fonction pour afficher plusieurs lignes (pr representer la FOV)
void ft_draw_lines(t_data *data)
{
	int i;
	double x;
	double y;
	double length;
	double line;
	double sav_angle;

	i = 0;
	sav_angle = data->angle;
	data->angle -= DEGREE * (FOV / 2);
	if (data->angle < 0)
		data->angle += 2 * M_PI;

	while (i < FOV)
	{
		x = 0;
		y = 0;
		line = 0;
		length = ft_length(data) * SIZE_CUBE;
		while (line < length)
		{
			my_mlx_pixel_put(&data->data_mlx.img, x + (SIZE_MINI_MAP / 2) * SIZE_CUBE, y + (SIZE_MINI_MAP / 2) * SIZE_CUBE, ft_rgb(255, 0, 0));
			x += cos(data->angle);
			y += sin(data->angle);
			line++;
			if ((x + (SIZE_MINI_MAP / 2) * SIZE_CUBE) > SIZE_MINI_MAP * SIZE_CUBE)
				break;
			if ((y + (SIZE_MINI_MAP / 2) * SIZE_CUBE) > SIZE_MINI_MAP * SIZE_CUBE)
				break;
		}
		data->angle += DEGREE;
		if (data->angle > 2 * M_PI)
		{
			data->angle -= 2 * M_PI;
		}
		i++;
	}
	data->angle = sav_angle;
}
