/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:26:43 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/15 11:34:44 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

#define	SIZE_SQUARE 10
#define	LENGHT_LINE 100
#define	WIDTH_LINE 5

void	ft_draw_lines(t_mlx *mlx)
{
	float x;
	float y;
	float lenght;
	for (float i = -0.5; i < 0.5; i = i + 0.1)
	{
		x = 0;
		y = 0;
		lenght = 0;
		while (lenght < 100)
		{
			my_mlx_pixel_put(&mlx->img, mlx->x + (int)x + SIZE_SQUARE / 2, mlx->y + (int)y + SIZE_SQUARE / 2, ft_rgb(0, 255, 0));
			x += cos(mlx->angle + i);
			y += sin(mlx->angle + i);
			lenght++;
		}
	}
}

void ft_draw_square(t_mlx *mlx)
{
	int x = 0;
	int y;
	while (x < SIZE_SQUARE)
	{
		y = 0;
		while (y < SIZE_SQUARE)
		{
			my_mlx_pixel_put(&mlx->img, x + mlx->x, y + mlx->y, ft_rgb(255, 0, 0));
			y++;
		}
		x++;
	}
}


int main(void)
{
	t_mlx mlx;

	// NOTE Position du joueur
	mlx.x = 100;
	mlx.y = 100;

	// NOTE	Orientation de la vue
	mlx.angle = 0;
	mlx.pdx = cos(0);
	mlx.pdy = sin(0);

	// NOTE Mlx de merde
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW, NAME_WINDOW);
	mlx.img.img = mlx_new_image(mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel, &mlx.img.line_length, &mlx.img.endian);

	ft_draw_square(&mlx);
	ft_draw_lines(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);

	// NOTE Gestion des touche du clavier
	mlx_hook(mlx.window, 2, 0, &ft_keyboard, &mlx);
	// NOTE Croix rouge
	mlx_hook(mlx.window, 17, 1L << 3, &ft_close_window, NULL);

	mlx_loop(mlx.mlx);
	return (0);
}
