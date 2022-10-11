/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:57:26 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/11 14:02:18 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static void	my_mlx_init_xpm(t_img_mlx *texture, t_mlx *data_mlx,
		char *path_to_file)
{
	texture->img = mlx_xpm_file_to_image(data_mlx->mlx, path_to_file,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error init texture: %s\n", path_to_file);
		exit(0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

static void	ft_set_dir(t_data *data, int x, int y)
{
	if (data->data_map.strmap[y][x] == 'N')
		data->angle = M_PI + M_PI_2;
	else if (data->data_map.strmap[y][x] == 'S')
		data->angle = M_PI_2;
	else if (data->data_map.strmap[y][x] == 'W')
		data->angle = M_PI;
	else
		data->angle = 0;
}

void	ft_init_tex(t_data *data)
{
	my_mlx_init_xpm(&data->data_tex.no, &data->data_mlx,
		data->data_map.no_texture);
	my_mlx_init_xpm(&data->data_tex.so, &data->data_mlx,
		data->data_map.so_texture);
	my_mlx_init_xpm(&data->data_tex.we, &data->data_mlx,
		data->data_map.we_texture);
	my_mlx_init_xpm(&data->data_tex.ea, &data->data_mlx,
		data->data_map.ea_texture);
}

unsigned int	my_mlx_pixel_get_color(t_img_mlx *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_init_player(t_data *data)
{
	data->pos.x = ft_colpos(data->data_map.strmap) + 0.5;
	data->pos.y = ft_linepos(data->data_map.strmap) + 0.5;
	ft_set_dir(data, data->pos.x, data->pos.y);
	data->dir.x = cos(data->angle);
	data->dir.y = sin(data->angle);
}
