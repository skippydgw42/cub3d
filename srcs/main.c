/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:56:05 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/12 10:23:59 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

// void	ft_printmap(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i])
// 	{
// 		printf("%s\n", map[i]);
// 		i++;
// 	}
// }

// void	ft_printmapstruct(t_map map)
// {
// 	printf("=================\n");
// 	printf("%s\n", map.map_name);
// 	printf("=================\n");
// 	printf("%s\n%s\n%s\n%s\n", map.no_texture, map.so_texture, map.we_texture,
// 			map.ea_texture);
// 	printf("\n======\n");
// 	printf("FLOOR\n");
// 	for (int x = 0; x < 3; x++)
// 	{
// 		printf("%d ", map.floor[x]);
// 	}
// 	printf("\n======\n");
// 	printf("CEILING\n");
// 	for (int x = 0; x < 3; x++)
// 	{
// 		printf("%d ", map.ceiling[x]);
// 	}
// 	printf("\n======\nMAP\n");
// 	ft_printmap(map.strmap);
// 	printf("\n======\nINT_MAP\n");
// 	printf("height:%d | max length:%d\n", map.height, map.width);
// 	for (int i = 0; i < map.height; i++)
// 	{
// 		for (int j = 0; j < map.width; j++)
// 		{
// 			printf("%d", map.map[i][j]);
// 		}
// 		printf("\n");
// 	}
// }

int	main(int ac, char **av)
{
	t_data	data;

	if (!ft_init_map(&data.data_map, av, ac))
		return (ft_return("====init===="));
	if (!ft_parsing(&data))
		return (ft_return("====parsing===="));
	data.data_mlx.mlx = mlx_init();
	data.data_mlx.window = mlx_new_window(data.data_mlx.mlx, WIDTH_WINDOW,
			HEIGHT_WINDOW, data.data_map.map_name);
	data.data_mlx.img.img = mlx_new_image(data.data_mlx.mlx, WIDTH_WINDOW,
			HEIGHT_WINDOW);
	data.data_mlx.img.addr = mlx_get_data_addr(data.data_mlx.img.img,
			&data.data_mlx.img.bits_per_pixel, &data.data_mlx.img.line_length,
			&data.data_mlx.img.endian);
	ft_init_tex(&data);
	ft_init_player(&data);
	ft_raycasting(&data);
	mlx_hook(data.data_mlx.window, 2, 0, &ft_keyboard, &data);
	mlx_hook(data.data_mlx.window, 17, 1L << 3, &ft_close_window, &data);
	mlx_loop(data.data_mlx.mlx);
	return (0);
}
