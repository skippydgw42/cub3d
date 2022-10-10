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

// NOTE A supprimer
#define MAP_WIDHT 16
#define MAP_HEIGHT 14


// void	ft_init_map(t_map *map)
// {
// 	int map_init[MAP_HEIGHT][MAP_WIDHT] = {
// 	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
// 	{0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
// 	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
// 	{1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
// 	{0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
// 	{0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
// 	{0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
// 	{0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1},
// 	{0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
// 	{0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
// 	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// 	int	y;
// 	int	x;

// 	y = 0;
// 	map->map = malloc(sizeof(int *) * map->height);
// 	if (!map->map)
// 	{
// 		perror("Cub3D:");
// 		exit(0);
// 	}
// 	while (y < map->height)
// 	{
// 		x = 0;
// 			map->map[y] = malloc(sizeof(int) * map->width);
// 		while (x < map->width)
// 		{
// 			map->map[y][x] = map_init[y][x];
// 			x++;
// 		}
// 		y++;
// 	}
// }

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

// REVIEW Changer les paths
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

int main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_return("====ac===="));
	if (!ft_init_map(&data.data_map, av))
		return (ft_return("====init===="));
	if (!ft_parsing(&data))
		return (ft_return("====parsing===="));
	ft_printmapstruct(data.data_map);

	// NOTE Mlx de merde
	// REVIEW leaks sur mon mac (Luca)
	data.data_mlx.mlx = mlx_init();
	data.data_mlx.window = mlx_new_window(data.data_mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW, data.data_map.map_name);
	data.data_mlx.img.img = mlx_new_image(data.data_mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
	data.data_mlx.img.addr = mlx_get_data_addr(data.data_mlx.img.img, &data.data_mlx.img.bits_per_pixel, &data.data_mlx.img.line_length, &data.data_mlx.img.endian);

	// NOTE Position du joueur
	data.pos.x = ft_colpos(data.data_map.strmap);
	data.pos.y = ft_linepos(data.data_map.strmap);

	// NOTE	Orientation de la vue
	data.angle = 0;
	data.dir.x = cos(0);
	data.dir.y = sin(0);

	// NOTE	Init texture
	ft_init_tex(&data);

	ft_raycasting(&data);

	// NOTE Gestion des touche du clavier
	mlx_hook(data.data_mlx.window, 2, 0, &ft_keyboard, &data);
	// NOTE Croix rouge
	mlx_hook(data.data_mlx.window, 17, 1L << 3, &ft_close_window, &data);

	mlx_loop(data.data_mlx.mlx);
	return (0);
}
