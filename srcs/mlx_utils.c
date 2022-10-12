/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:41:10 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/12 09:07:10 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_free_array(data->data_map.height, data->data_map.map);
	ft_freemap(&data->data_map);
	exit(0);
}

void	my_mlx_pixel_put(t_img_mlx *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH_WINDOW || y >= HEIGHT_WINDOW)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_move(t_data *data, int keycode)
{
	data->dir.x = cos(data->angle) * 0.3;
	data->dir.y = sin(data->angle) * 0.3;
	if (keycode == DOWN || keycode == S)
	{
		data->dir.x *= -1;
		data->dir.y *= -1;
		data->angle += M_PI;
	}
	if (!data->data_map.map[(int)data->pos.y][(int)(data->pos.x + data->dir.x)])
		data->pos.x += data->dir.x;
	if (!data->data_map.map[(int)(data->pos.y + data->dir.y)][(int)data->pos.x])
		data->pos.y += data->dir.y;
	if (keycode == DOWN || keycode == S)
		data->angle -= M_PI;
}

int	ft_keyboard(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_close_window(data);
	else if (keycode == A || keycode == LEFT)
	{
		if (data->angle <= 0)
			data->angle += 2.0 * M_PI;
		data->angle -= 0.05;
	}
	else if (keycode == S || keycode == DOWN)
		ft_move(data, keycode);
	else if (keycode == D || keycode == RIGHT)
	{
		if (data->angle > 2.0 * M_PI)
			data->angle -= 2.0 * M_PI;
		data->angle += 0.05;
	}
	else if (keycode == W || keycode == UP)
		ft_move(data, keycode);
	ft_raycasting(data);
	return (EXIT_SUCCESS);
}
