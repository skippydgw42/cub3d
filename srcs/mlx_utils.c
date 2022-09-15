/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:38:42 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/09/15 11:33:51 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

void	ft_draw_ceiling(t_mlx *mlx, int color)
{
	int x;
	int	y;

	x = 0;
	while (x < WIDTH_WINDOW)
	{
		y = 0;
		while (y < HEIGHT_WINDOW / 2)
		{
			my_mlx_pixel_put(&mlx->img, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_draw_floor(t_mlx *mlx, int color)
{
	int x;
	int	y;

	x = 0;
	while (x < WIDTH_WINDOW)
	{
		y = HEIGHT_WINDOW / 2;
		while (y < HEIGHT_WINDOW)
		{
			my_mlx_pixel_put(&mlx->img, x, y, color);
			y++;
		}
		x++;
	}
}

int		ft_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return ((red * 256 * 256) + (green * 256) + blue);
}

int		ft_close_window(void *param)
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

int		ft_keyboard(int keycode, t_mlx *mlx)
{
	// NOTE fonction qui ne sera plus utile dans la suite du projet
	my_mlx_clear_window(mlx);
	// 
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit(0);
	}
	else if (keycode == A || keycode == LEFT)
	{
		if (mlx->angle < 0)
		{
			mlx->angle = 2.0 * PI;
		}
		mlx->angle -= 0.1;
		mlx->pdx = cos(mlx->angle);
		mlx->pdy = sin(mlx->angle);
	}
	else if (keycode == S || keycode == DOWN)
	{
		mlx->x -= mlx->pdx * 5.0;
		mlx->y -= mlx->pdy * 5.0;
	}
	else if (keycode == D || keycode == RIGHT)
	{
		if (mlx->angle > 2.0 * PI)
		{
			mlx->angle = 0;
		}
		mlx->angle += 0.1;
		mlx->pdx = cos(mlx->angle);
		mlx->pdy = sin(mlx->angle);
	}
	else if (keycode == W || keycode == UP)
	{
		mlx->x += mlx->pdx * 5.0;
		mlx->y += mlx->pdy * 5.0;
	}
	ft_draw_square(mlx);
	ft_draw_lines(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
	return (EXIT_SUCCESS);
}

// NOTE A supprimer
void	my_mlx_clear_window(t_mlx *mlx)
{
	int x = 0;
	int	y;
	while (x < WIDTH_WINDOW)
	{
		y = 0;
		while (y < HEIGHT_WINDOW)
		{
			my_mlx_pixel_put(&mlx->img, x, y, ft_rgb(0, 0, 0));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
