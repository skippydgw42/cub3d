/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:53:05 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/06 14:13:44 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

void ft_raycasting(t_data *data)
{
	double old_angle;

	ft_draw_ceiling(data, ft_rgb(200, 200, 200));
	ft_draw_floor(data, ft_rgb(125, 125, 125));
	old_angle = data->angle;
	data->angle -= DEGREE * (FOV / 2);
	if (data->angle < 0)
		data->angle += (2 * M_PI);
	for (int i = 0; i <= (FOV * RESOLUTION) - 1; i++)
	{
		ft_draw_wall(data, (ft_length(data)) * cos(fabs(old_angle - data->angle)), i, data->orientation);
		data->angle += DEGREE / RESOLUTION;
	}
	data->angle = old_angle;
	ft_draw_map(data);
	ft_draw_lines(data);
	mlx_put_image_to_window(data->data_mlx.mlx, data->data_mlx.window, data->data_mlx.img.img, 0, 0);
}
