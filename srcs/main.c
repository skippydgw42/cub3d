/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:26:43 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/14 11:44:58 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return ((red * 256 * 256) + (green * 256) + blue);
}

int	ft_close_window(void *param)
{
	(void)param;
	exit(0);
}

void	my_mlx_pixel_put(t_data_img_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_draw_square(t_mlx *mlx)
{
	int x = 0;
	int	y;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(&mlx->img, x + mlx->x, y + mlx->y, ft_rgb(255, 0, 0));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}

void	my_mlx_clear_window(t_mlx *mlx)
{
	int x = 0;
	int	y;
	while (x < WIDTH_WINDOW)
	{
		y = 0;
		while (y < HEIGHT_WINDOW)
		{
			my_mlx_pixel_put(&mlx->img, x + mlx->x, y + mlx->y, ft_rgb(0, 0, 0));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}

int	ft_keyboard(int keycode, t_mlx *mlx)
{
	my_mlx_clear_window(mlx);
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit(0);
	}
	else if (keycode == A || keycode == LEFT)
	{
		(mlx->x)--;
	}
	else if (keycode == S || keycode == DOWN)
	{
		(mlx->y)++;
	}
	else if (keycode == D || keycode == RIGHT)
	{
		(mlx->x)++;
	}
	else if (keycode == W || keycode == UP)
	{
		(mlx->y)--;
	}
	ft_draw_square(mlx);
	return (EXIT_SUCCESS);
}

int main(void)
{
	t_mlx mlx;

	mlx.x = 0;
	mlx.y = 0;
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW, NAME_WINDOW);
	mlx.img.img = mlx_new_image(mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel, &mlx.img.line_length, &mlx.img.endian);

	ft_draw_square(&mlx);

	// NOTE Gestion des touche du clavier
	mlx_key_hook(mlx.window, &ft_keyboard, &mlx);

	// NOTE Croix rouge
	mlx_hook(mlx.window, 17, 1L << 3, &ft_close_window, NULL);

	mlx_loop(mlx.mlx);
	return (0);
}
