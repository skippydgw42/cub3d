/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:26:43 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/22 17:17:46 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

// static int map[MAP_HEIGHT][MAP_WIDHT] = {
// 	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
// 	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
// 	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// 	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// 	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
// 	{1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
// 	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// 	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// 	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
// 	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
// 	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// 	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

double	ft_ml_hor(double angle, t_mlx *mlx)
{
	double	length;

	if (angle > 0 && angle < PI)
		length = ft_decalage_y(mlx) / sin(angle);
	else
		length = (ft_decalage_y(mlx) - 32) / sin(angle);
	return (length);
}

double	ft_ml_ver(double angle, t_mlx *mlx)
{
	double	length;

	if (angle > PI / 2 && angle < 3 * PI / 2)
		length = (ft_decalage_x(mlx) - 32) / cos(angle);
	else
		length = ft_decalage_x(mlx) / cos(angle);
	return (length);
}


double ft_lenght_hor(double angle, t_mlx *mlx)
{
	double length;
	double x;
	double y;
	
	length = ft_ml_hor(angle, mlx);
	x = ft_find_x(length, angle);
	y = ft_find_y(length, angle);
	// ft_draw_point(mlx, x, y, ft_rgb(255, 255, 0));

	while (1)
	{
		if (angle >= 0 && angle < PI)
		{
			if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y), angle, 0))
				return (length);
			else if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y - SIZE_CUBE), angle, 0))
				return (length);
		}
		else
		{
			if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y - SIZE_CUBE), angle, 0))
				return (length);
			else if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y), angle, 0))
				return (length);
		}
		length += fabs(32.0 / sin(angle));
		x = ft_find_x(length, angle);
		y = ft_find_y(length, angle);
		// ft_draw_point(mlx, x, y, ft_rgb(255, 0, 0));
		if (length > WIDTH_WINDOW)
			break ;
	}
	return (length);
}

double ft_lenght_ver(double angle, t_mlx *mlx)
{
	double length;
	double x;
	double y;

	length = ft_ml_ver(angle, mlx);
	x = ft_find_x(length, angle);
	y = ft_find_y(length, angle);
	// ft_draw_point(mlx, x, y, ft_rgb(255, 255,0));

	while (1)
	{
		if (angle >= PI / 2 && angle < 3 * PI / 2)
		{
			if (ft_check_wall(lround(x + mlx->x - SIZE_CUBE), lround(y + mlx->y), angle, 1))
				return (length);
			else if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y), angle, 0))
				return (length);
		}
		else
		{
			if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y), angle, 1))
				return (length);
			else if (ft_check_wall(lround(x + mlx->x - SIZE_CUBE), lround(y + mlx->y), angle, 0))
				return (length);
		}
		length += fabs(32.0 / cos(angle));
		x = ft_find_x(length, angle);
		y = ft_find_y(length, angle);
		// ft_draw_point(mlx, x, y, ft_rgb(255, 0,0));
		if (length > HEIGHT_WINDOW)
			break ;
	}
	return (length);
}

int main(void)
{
	t_mlx mlx;

	// NOTE Position du joueur
	mlx.x = 255;
	mlx.y = 223;

	// NOTE	Orientation de la vue
	mlx.angle = 4.249876;
	mlx.dx = cos(0);
	mlx.dy = sin(0);

	// NOTE Mlx de merde
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW, NAME_WINDOW);
	mlx.img.img = mlx_new_image(mlx.mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel, &mlx.img.line_length, &mlx.img.endian);

	// ft_draw_map(&mlx);
	ft_draw_map(&mlx);
	ft_draw_grid(&mlx);
	ft_draw_lines(&mlx);
	// ft_draw_square(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);

	// NOTE Gestion des touche du clavier
	mlx_hook(mlx.window, 2, 0, &ft_keyboard, &mlx);
	// NOTE Croix rouge
	mlx_hook(mlx.window, 17, 1L << 3, &ft_close_window, NULL);

	mlx_loop(mlx.mlx);
	return (0);
}
