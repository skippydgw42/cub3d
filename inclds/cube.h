/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:20:09 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/22 16:30:18 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../mlib/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>

// Config
# define PI	3.141593
# define WIDTH_WINDOW 540
# define HEIGHT_WINDOW 480
# define NAME_WINDOW "42_cub3D"
#define SIZE_CUBE 32

// Keyboard
# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

#define SIZE_SQUARE 10
#define LENGHT_LINE 100
#define WIDTH_LINE 5

#define SIZE_CUBE 32
#define MAP_WIDHT 16
#define MAP_HEIGHT 14

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img_mlx;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	float			x;
	float			y;
	float			dx;
	float			dy;
	float			angle;
	t_data_img_mlx	img;
}	t_mlx;

// NOTE A supprimer (pour des tests)
void	ft_draw_square(t_mlx *mlx);
void	ft_draw_lines(t_mlx *mlx);
void	ft_draw_map(t_mlx *mlx);
void	ft_draw_grid(t_mlx *mlx);

// mlx_utils
int		ft_rgb(unsigned char red, unsigned char green, unsigned char blue);
int		ft_close_window(void *param);
int		ft_keyboard(int keycode, t_mlx *mlx);
void	my_mlx_pixel_put(t_data_img_mlx *data, int x, int y, int color);
void	my_mlx_clear_window(t_mlx *mlx);

//effective functions
void	ft_draw_dir(t_mlx *mlx);
double	ft_lenght(double angle, t_mlx *mlx);
void	ft_draw_point(t_mlx *mlx, int x, int y, int color);
float	ft_decalage_y(t_mlx *mlx);
float	ft_decalage_x(t_mlx *mlx);
double	ft_find_x(double hypo, double angle);
double	ft_find_y(double hypo, double angle);
void	ft_draw_block(t_mlx *mlx, int pos_x, int pos_y);

double	ft_lenght_hor(double angle, t_mlx *mlx);
double	ft_lenght_ver(double angle, t_mlx *mlx);
int		ft_check_wall(int x, int y, double angle, int rev);
int		ft_angle(double angle);

#endif
