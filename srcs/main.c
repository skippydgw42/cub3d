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

#define SIZE_SQUARE 10
#define LENGHT_LINE 100
#define WIDTH_LINE 5

#define SIZE_CUBE 32
#define MAP_WIDHT 16
#define MAP_HEIGHT 14

int map[MAP_HEIGHT][MAP_WIDHT] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

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

// NOTE Checker si j'ai touche un mur
int ft_check_wall(int x, int y)
{
	// NOTE A permit de regler le probleme d'affichage dans certain cas mais c'est un peu de la merde
	printf("Wall: x=%d y=%d\n", x / 32, y / 32);
	if (y / 32 > MAP_HEIGHT || x / 32 > MAP_WIDHT || y < 0 || x < 0)
		return (0);
	return (map[y / 32][x / 32]);
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

double ft_lenght_hor(double angle, t_mlx *mlx)
{
	double lenght;
	double x;
	double y;

	// NOTE si je regarder vers le bas
	if (angle > 0 && angle < PI)
	{
		lenght = ft_decalage_y(mlx) / sin(angle);
	}
	// NOTE sinon je regarder vers le haut
	else
	{
		lenght = (ft_decalage_y(mlx) - 32) / sin(angle);
	}
	x = ft_find_x(lenght, angle);
	y = ft_find_y(lenght, angle);
	// ft_draw_point(mlx, x, y, ft_rgb(255, 255, 0));
	while (1)
	{
	// NOTE si je regarder vers le bas
		if (angle > 0 && angle < PI)
		{
			if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y)))
				return (lenght);
		}
	// NOTE sinon je regarder vers le haut
		else
		{
			if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y - SIZE_CUBE)))
				return (lenght);
		}
		lenght += fabs(32.0 / sin(angle));
		x = ft_find_x(lenght, angle);
		y = ft_find_y(lenght, angle);
		// ft_draw_point(mlx, x, y, ft_rgb(255, 0, 0));
		if (lenght > WIDTH_WINDOW)
			break;
	}
	return (lenght);
}

double ft_lenght_ver(double angle, t_mlx *mlx)
{
	double lenght;
	double x;
	double y;

	// NOTE Je regarder vers la gauche
		if (angle > PI / 2 && angle < 3 * PI / 2)
	{

	lenght = (ft_decalage_x(mlx) - 32) / cos(angle);
	}
	// NOTE Je regarder vers la droite
	else
	{
	lenght = ft_decalage_x(mlx) / cos(angle);

	}
		x = ft_find_x(lenght, angle);
		y = ft_find_y(lenght, angle);
		// ft_draw_point(mlx, x, y, ft_rgb(255, 255,0));
	while (1)
	{
	// NOTE Je regarder vers la gauche
		if (angle > PI / 2 && angle < 3 * PI / 2)
		{
			if (ft_check_wall(lround(x + mlx->x - SIZE_CUBE), lround(y + mlx->y)))
				return (lenght);
		}
	// NOTE Je regarder vers la droite
		else
		{
			if (ft_check_wall(lround(x + mlx->x), lround(y + mlx->y)))
				return (lenght);
		}
		lenght += fabs(32.0 / cos(angle));
		x = ft_find_x(lenght, angle);
		y = ft_find_y(lenght, angle);
	// ft_draw_point(mlx, x, y, ft_rgb(255, 0,0));
		if (lenght > HEIGHT_WINDOW)
			break;
	}
	return (lenght);
}

double ft_lenght(double angle, t_mlx *mlx)
{
	int lenght_ver;
	int lenght_hor;

	lenght_ver = roundl(ft_lenght_ver(angle, mlx));
	lenght_hor = roundl(ft_lenght_hor(angle, mlx));
	if (lenght_hor < lenght_ver && lenght_hor > 0)
		return (lenght_hor);
	return (lenght_ver);
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
	while (length < 100)
	{
		my_mlx_pixel_put(&mlx->img, x + mlx->x, y + mlx->y, ft_rgb(255, 0, 0));
		x += cos(mlx->angle);
		y += sin(mlx->angle);
		length++;
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
	for (int i = 0; i < 1; i++)
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
	}
	mlx->angle = tmp;
	ft_draw_dir(mlx);
}

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

int main(void)
{
	t_mlx mlx;

	// NOTE Position du joueur
	mlx.x = 245;
	mlx.y = 225;

	// NOTE	Orientation de la vue
	mlx.angle = 3;
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
