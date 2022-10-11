/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:56:05 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/11 14:52:36 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

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
