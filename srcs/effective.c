/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effective.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:34:51 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/22 17:08:49 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static int map[MAP_HEIGHT][MAP_WIDHT] = {
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
	{1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

// NOTE Dessiner un petit carre rouge pour representer le perso
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

// NOTE Dessiner une ligne rouge pour indiquer la direction
void ft_draw_dir(t_mlx *mlx)
{
	double length;
	double x;
	double y;

	length = 0;
	x = 0;
	y = 0;
	while (length < 50)
	{
		my_mlx_pixel_put(&mlx->img, x + mlx->x, y + mlx->y, ft_rgb(255, 0, 0));
		x += cos(mlx->angle);
		y += sin(mlx->angle);
		length++;
	}
}

double ft_lenght(double angle, t_mlx *mlx)
{
	int length_ver;
	int length_hor;

	length_ver = roundl(ft_lenght_ver(angle, mlx));
	length_hor = roundl(ft_lenght_hor(angle, mlx));
	if (length_hor < length_ver && length_hor > 0)
		return (length_hor);
	return (length_ver);
}

// NOTE dessiner les points d'intersection
void ft_draw_point(t_mlx *mlx, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(&mlx->img, mlx->x + x + i, mlx->y + y + j, color);
			j++;
		}
		i++;
	}
}

// NOTE Decalage sur l'axe de y
float ft_decalage_y(t_mlx *mlx)
{
	int i;
	float etapes;

	etapes = 0;
	i = 0;
	while (etapes < mlx->y)
	{
		i++;
		etapes = i * SIZE_CUBE;
	}
	return (etapes - mlx->y);
}

// NOTE Decalage sur l'axe de X
float ft_decalage_x(t_mlx *mlx)
{
	int i;
	float etapes;

	etapes = 0;
	i = 0;
	while (etapes < mlx->x)
	{
		i++;
		etapes = i * SIZE_CUBE;
	}
	return (etapes - mlx->x);
}

// NOTE Trouver la longueur de x
double ft_find_x(double hypo, double angle)
{
	return (cos(angle) * hypo);
}

// NOTE Trouver la longueur de y
double ft_find_y(double hypo, double angle)
{
	return (sin(angle) * hypo);
}

// NOTE Dessiner tous les blocs de la map
void ft_draw_map(t_mlx *mlx)
{
	int i;
	int j;
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDHT)
		{
			if (map[i][j] == 1)
			{
				ft_draw_block(mlx, j * SIZE_CUBE, i * SIZE_CUBE);
			}
			j++;
		}
		i++;
	}
}

// NOTE Dessiner un bloc de la map
void ft_draw_block(t_mlx *mlx, int pos_x, int pos_y)
{
	int x;
	int y;

	x = 0;
	while (x < SIZE_CUBE - 1)
	{
		y = 0;
		while (y < SIZE_CUBE - 1)
		{
			my_mlx_pixel_put(&mlx->img, x + pos_x, y + pos_y, ft_rgb(255, 255, 255));
			y++;
		}
		x++;
	}
}

// NOTE Fonction un peu claque pour afficher plusieurs lignes
void ft_draw_lines(t_mlx *mlx)
{
	double x;
	double y;
	double lenght;
	double tmp;

	tmp = mlx->angle;
	mlx->angle -= PI / 180 * 30;
	for (int i = 0; i < 60; i++)
	{
		x = 0;
		y = 0;
		lenght = 0;
		double test = ft_lenght(mlx->angle, mlx);
		while (lenght < test)
		{
			my_mlx_pixel_put(&mlx->img, x + mlx->x, y + mlx->y, ft_rgb(0, 255, 0));
			x += cos(mlx->angle);
			y += sin(mlx->angle);
			lenght++;
			if (lenght >= 1000)
				break;
		}
		// printf("x:%f y:%f angle:%f lenght:%f\n", mlx->x, mlx->y, mlx->angle, lenght);
		// fflush(stdout);
		mlx->angle += PI / 180;
		if (mlx->angle > 2 * PI)
			mlx->angle -= 2 * PI;
	}
	mlx->angle = tmp;
	// ft_draw_dir(mlx);
}