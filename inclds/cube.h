/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:20:09 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/15 11:36:04 by ltrinchi         ###   ########lyon.fr   */
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
	float			pdx;
	float			pdy;
	float			angle;
	t_data_img_mlx	img;
}	t_mlx;

// NOTE A supprimer (pour des tests)
void	ft_draw_square(t_mlx *mlx);
void	ft_draw_lines(t_mlx *mlx);

// mlx_utils
int		ft_rgb(unsigned char red, unsigned char green, unsigned char blue);
int		ft_close_window(void *param);
int		ft_keyboard(int keycode, t_mlx *mlx);
void	my_mlx_pixel_put(t_data_img_mlx *data, int x, int y, int color);
void	my_mlx_clear_window(t_mlx *mlx);

#endif
