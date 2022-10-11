/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:20:09 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 15:11:45 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/srcs/libft.h"
# include "../mlib/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

// Config
# define WIDTH_WINDOW 720
# define HEIGHT_WINDOW 640

// Draw
# define SIZE_CUBE 15
# define SIZE_MINI_MAP 8
# define RESOLUTION 50.0
# define FOV 60.0
# define DEGREE 0.01745329252

// DDA
# define HOR 0
# define VER 1

// Draw && DDA
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4
# define WALL 1
# define FLOOR 0

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

typedef struct s_img_mlx
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_img_mlx;

typedef struct s_texture
{
	t_img_mlx	no;
	t_img_mlx	so;
	t_img_mlx	we;
	t_img_mlx	ea;
	double		ratio_x;
	double		height;
	double		verti_shift;
}				t_texture;
typedef struct s_map
{
	int			**map;
	int			height;
	int			width;
	char		**strmap;
	char		*map_name;
	char		*no_texture;
	int			no;
	char		*so_texture;
	int			so;
	char		*we_texture;
	int			we;
	char		*ea_texture;
	int			ea;
	int			*floor;
	int			*ceiling;
}				t_map;
typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_img_mlx	img;
	t_texture	tex;
}				t_mlx;

typedef struct s_data
{
	t_mlx		data_mlx;
	t_coord		pos;
	double		angle;
	t_coord		dir;
	t_map		data_map;
	int			orientation;
	t_texture	data_tex;
}				t_data;

//DEL
void			ft_printmapstruct(t_map map);
void			ft_printmap(char **map);

//ADD
// void	ft_freemap(t_map map);
int				ft_return(char *str);
int				ft_close_fd(int fd, int ret);
int				ft_free_init(t_map *map, char *flat_map);
void			ft_free_texture_path(t_map *map);
int				ft_freemap(t_map *map);

//INIT
int				*ft_set_forc(void);
int				ft_skipspaces(char *str);
int				ft_check_rgb_val(int *tab);
int				ft_check_path(char *str);
void			ft_chooseparam(t_map *map, char *flat_map, char *old_path);
char			*ft_get_path(char *str);
char			*ft_preatoi(char *flat_map);
char			*ft_cpyline(char *flat_map);
int				ft_length_path(char *str);
void			ft_take_rgb_ceiling(t_map *map, char *flat_map, int x);
void			ft_take_rgb_floor(t_map *map, char *flat_map, int x);
void			ft_take_texture(t_map *map, char *flat_map, int x);
int				ft_mapsize(char *flat_map, int x);
int				ft_check_closed(char **map);
int				ft_check_char(char **map);
int				ft_check_extension(char *path, char *ext);
char			*ft_getflat(int fd);
int				ft_setparams(t_map *map, char *flat_map);
int				ft_setmap(t_map *map, char *flat_map, int x);
int				ft_to_map(char *flat_map, int x);
void			ft_imap(t_map *map);
void			ft_init_player(t_data *data);
void			ft_init_tex(t_data *data);

//PARSING
int				ft_init_map(t_map *map, char **av, int ac);
int				ft_parsing(t_data *data);
int				ft_recursive(char **map, int i, int j);
int				ft_colpos(char **map);
int				ft_linepos(char **map);
int				ft_clist(char c);

int				ft_coord_check(char **map);

// draw
int				ft_rgb(unsigned char red, unsigned char green,
					unsigned char blue);
void			ft_draw_wall(t_data *data, double length, int pos, int dir);
void			ft_draw_ceiling(t_data *data, int color);
void			ft_draw_floor(t_data *data, int color);

// free
void			ft_free_array(int size, int **tab);

// minimap
void			ft_draw_map(t_data *data);
void			ft_draw_fov(t_data *data, int color);
int				ft_check_map(t_data *data, int x, int y);

// DDA_algo
int				ft_check_wall(t_coord coord, t_data *data, int opt);
double			ft_length(t_data *data);

// Raycasting
void			ft_raycasting(t_data *data);

// mlx_utils
int				ft_close_window(void *param);
int				ft_keyboard(int keycode, t_data *data);
void			my_mlx_pixel_put(t_img_mlx *img, int x, int y, int color);
unsigned int	my_mlx_pixel_get_color(t_img_mlx *img_data, int x, int y);

#endif
