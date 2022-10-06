/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:22:43 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/05 16:52:15 by ltrinchi         ###   ########lyon.fr   */
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

// NOTE Dessiner tous les blocs de la map
void ft_draw_map(t_data *data)
{
	int x;
	int y;
	x = 0;
	while (x < data->data_map.width)
	{
		y = 0;
		while (y <	data->data_map.height)
		{
			if (data->data_map.map[y][x] == WALL)
				ft_draw_square(data, x * SIZE_CUBE, y * SIZE_CUBE, 0xffffff, SIZE_CUBE);
			else
				ft_draw_square(data, x * SIZE_CUBE, y * SIZE_CUBE, 0x000000, SIZE_CUBE);
			y++;
		}
		x++;
	}
}

// NOTE Fonction pour afficher plusieurs lignes (pr representer la FOV)
void ft_draw_lines(t_data *data)
{
	int		i;
	double	x;
	double	y;
	double	length;
	double	line;
	double	sav_angle;


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
			my_mlx_pixel_put(&data->data_mlx.img, x + data->pos.x * SIZE_CUBE, y + data->pos.y * SIZE_CUBE, ft_rgb(255, 0, 0));
			x += cos(data->angle);
			y += sin(data->angle);
			line++;
		}
		// printf("x:%f y:%f angle:%f length:%f\n", mlx->x, mlx->y, mlx->angle, length);
		data->angle += DEGREE;
		if (data->angle > 2 * M_PI)
		{
			data->angle -= 2 * M_PI;
		}
		i++;
	}
	data->angle = sav_angle;
}
