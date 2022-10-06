/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:20:09 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/05 17:12:05 by ltrinchi         ###   ########lyon.fr   */
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
# define WIDTH_WINDOW 720
# define HEIGHT_WINDOW 640
# define NAME_WINDOW "42_cub3D"

// Draw
# define SIZE_CUBE 10.0
# define RESOLUTION 50.0
# define FOV 60.0
# define DEGREE (2 * M_PI) / 360
# define WALL 1

// DDA
# define HOR 0
# define VER 1

// Draw && DDA
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4

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

typedef struct	s_img_mlx {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_img_mlx;

typedef struct s_texture
{
	t_img_mlx	NO;
	t_img_mlx	SO;
	t_img_mlx	WE;
	t_img_mlx	EA;
	double		start;
	double		height;
	double		verti_shift;
	double		ratio;
}	t_texture;

typedef	struct s_map
{
	int	height;
	int	width;
	int	**map;
}	t_map;

typedef	struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	t_img_mlx		img;
	t_texture		tex;
}	t_mlx;

typedef	struct s_data
{
	t_mlx		data_mlx;
	t_coord		pos;
	double		angle;
	t_coord		dir;
	t_map		data_map;
	int			orientation;
	t_texture	data_tex;
}	t_data;


// draw
int		ft_rgb(unsigned char red, unsigned char green, unsigned char blue);
void	ft_draw_wall(t_data *data, double length, int pos, int dir);
void	ft_draw_ceiling(t_data *data, int color);
void	ft_draw_floor(t_data *data, int color);

// free
void	ft_free_2D_array(int heigth, int width, int **tab);

// minimap
void	ft_draw_square(t_data *data, int pos_x, int pos_y, int color, int size);
void	ft_draw_map(t_data *data);
void	ft_draw_lines(t_data *data);

// DDA_algo
int		ft_check_wall(double x, double y, t_data *data, int opt);
double	ft_length(t_data *data);

// Raycasting
void	ft_raycasting(t_data *data);

// mlx_utils
int				ft_close_window(void *param);
int				ft_keyboard(int keycode, t_data *data);
void			my_mlx_pixel_put(t_img_mlx *img, int x, int y, int color);
unsigned int	my_mlx_pixel_get_color(t_img_mlx *img_data, int x, int y);

#endif
