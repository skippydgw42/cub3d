/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:26:43 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/15 17:50:48nchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

void	ft_printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	ft_printmapstruct(t_map map)
{
	printf("=================\n");
	printf("%s\n", map.map_name);
	printf("=================\n");
	printf("%s\n%s\n%s\n%s\n", map.no_texture, map.so_texture, map.we_texture, map.ea_texture);
	printf("\n======\n");
	printf("FLOOR\n");
	for (int x = 0; x < 3; x++)
	{
		printf("%d ", map.floor[x]);
	}
	printf("\n======\n");
	printf("CEILING\n");
	for (int x = 0; x < 3; x++)
	{
		printf("%d ", map.ceiling[x]);
	}
	printf("\n======\nMAP\n");
	ft_printmap(map.strmap);
	printf("\n======\nINT_MAP\n");
	printf("height:%d | max length:%d\n", map.height, map.width);
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.width; j++)
		{
			printf("%d", map.map[i][j]);
		}
		printf("\n");
	}
}


void	my_mlx_init_xpm(t_img_mlx *texture, t_mlx *data_mlx, char *path_to_file)
{
	texture->img = mlx_xpm_file_to_image(data_mlx->mlx, path_to_file, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error init texture: %s\n", path_to_file);
		exit(0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void	ft_init_tex(t_data *data)
{
	my_mlx_init_xpm(&data->data_tex.NO, &data->data_mlx, data->data_map.no_texture);
	my_mlx_init_xpm(&data->data_tex.SO, &data->data_mlx, data->data_map.so_texture);
	my_mlx_init_xpm(&data->data_tex.WE, &data->data_mlx, data->data_map.we_texture);
	my_mlx_init_xpm(&data->data_tex.EA, &data->data_mlx, data->data_map.ea_texture);
}

unsigned int	my_mlx_pixel_get_color(t_img_mlx *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	ft_set_dir(t_data *data, int x, int y)
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

void	ft_init_player(t_data *data)
{
	data->pos.x = ft_colpos(data->data_map.strmap) + 0.5;
	data->pos.y = ft_linepos(data->data_map.strmap) + 0.5;
	ft_set_dir(data, data->pos.x, data->pos.y);
	data->dir.x = cos(data->angle);
	data->dir.y = sin(data->angle);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_return("====ac===="));
	if (!ft_init_map(&data.data_map, av))
		return (ft_return("====init===="));
	if (!ft_parsing(&data))
	{
		// ft_freemap(&data.data_map);
		return (ft_return("====parsing===="));
	}
	// ft_printmapstruct(data.data_map);
	// NOTE Mlx de merde
	data.data_mlx.mlx = mlx_init();
	data.data_mlx.window = mlx_new_window(data.data_mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW, data.data_map.map_name);
	data.data_mlx.img.img = mlx_new_image(data.data_mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
	data.data_mlx.img.addr = mlx_get_data_addr(data.data_mlx.img.img, &data.data_mlx.img.bits_per_pixel, &data.data_mlx.img.line_length, &data.data_mlx.img.endian);


	// NOTE	Init texture
	ft_init_tex(&data);

	ft_init_player(&data);

	ft_raycasting(&data);

	// NOTE Gestion des touche du clavier
	mlx_hook(data.data_mlx.window, 2, 0, &ft_keyboard, &data);
	// NOTE Croix rouge
	mlx_hook(data.data_mlx.window, 17, 1L << 3, &ft_close_window, &data);

	mlx_loop(data.data_mlx.mlx);
	return (0);
}
