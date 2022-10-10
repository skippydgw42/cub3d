/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:58:08 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/10 17:06:21 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static void	ft_draw_line(t_data *data, int color)
{
	t_coord	coord;
	double	line;
	double	length;

	coord.x = 0;
	coord.y = 0;
	line = 0;
	length = ft_length(data) * SIZE_CUBE;
	while (line < length)
	{
		my_mlx_pixel_put(&data->data_mlx.img, coord.x + (SIZE_MINI_MAP / 2)
			* SIZE_CUBE, coord.y + (SIZE_MINI_MAP / 2) * SIZE_CUBE,
			color);
		coord.x += cos(data->angle);
		coord.y += sin(data->angle);
		line++;
		if ((coord.x + (SIZE_MINI_MAP / 2) * SIZE_CUBE) > SIZE_MINI_MAP
			* SIZE_CUBE)
			break ;
		if ((coord.y + (SIZE_MINI_MAP / 2) * SIZE_CUBE) > SIZE_MINI_MAP
			* SIZE_CUBE)
			break ;
	}
}

void	ft_draw_fov(t_data *data, int color)
{
	int		i;
	double	sav_angle;

	i = 0;
	sav_angle = data->angle;
	data->angle -= DEGREE * (FOV / 2);
	if (data->angle < 0)
		data->angle += 2 * M_PI;
	while (i < FOV)
	{
		ft_draw_line(data, color);
		data->angle += DEGREE;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		i++;
	}
	data->angle = sav_angle;
}
