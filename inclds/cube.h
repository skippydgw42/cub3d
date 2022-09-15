/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:20:09 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/15 17:50:13 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../mlib/mlx.h"
# include "../libft/srcs/libft.h"
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

typedef struct	s_map
{
	char	*map_name;
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		*floor;
	int		*ceiling;
}	t_map;

// NOTE A supprimer (pour des tests)
void	ft_draw_square(t_mlx *mlx);
void	ft_draw_lines(t_mlx *mlx);

// mlx_utils
int		ft_rgb(unsigned char red, unsigned char green, unsigned char blue);
int		ft_close_window(void *param);
int		ft_keyboard(int keycode, t_mlx *mlx);
void	my_mlx_pixel_put(t_data_img_mlx *data, int x, int y, int color);
void	my_mlx_clear_window(t_mlx *mlx);

//==============PARSING=============//
char	*ft_getflat(int fd);
t_map	*ft_init_map(int fd);

#endif
