/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 11:04:01 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/02 13:34:51 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define BUFF_SIZE 32
# include <fcntl.h>
# include <unistd.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <X11/Xlib.h>
# include <string.h>
# include "libft/libft.h"
# include <math.h>
# include <sys/time.h>

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_steve
{
	t_color			north;
	t_color			south;
	t_color			west;
	t_color			east;
}					t_steve;

typedef struct		s_inputs
{
	int				up;
	int				down;
	int				right;
	int				left;
}					t_inputs;

typedef struct		s_draw
{
	double			camerax;
	double			ray_posx;
	double			ray_posy;
	double			ray_dirx;
	double			ray_diry;
	int				mapx;
	int				mapy;
	double			side_distx;
	double			side_disty;
	double			delta_distx;
	double			delta_disty;
	double			perp_wall_dist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				x;
	t_color			c;
}					t_draw;

typedef struct		s_move
{
	struct timeval	time;
	long			usec;
	long			sec;
	double			movespeed;
	double			rotspeed;
	double			old_dirx;
	double			old_planex;
}					t_move;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	t_steve			s;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			time;
	double			old_time;
	double			frame_time;
	double			planex;
	double			planey;
	int				**world_map;
	t_inputs		inputs;
	t_draw			draw;
	t_move			move;
	int				map[MAP_WIDTH][MAP_HEIGHT];
}					t_env;

void				calc_steps_and_side_dist(t_env *e);
void				calc_wall_dist(t_env *e);
void				calc_line_height(t_env *e);

void				put_pixel_to_img(t_env *e, int x, int y, t_color *c);
void				vertical_line(t_env *e, int x, int start, int end);
void				to_next_square(t_env *e);
void				change_position(t_env *e);
void				ft_draw(t_env *e);

void				get_color(int r, int g, int b, t_color *get);
void				init_draw(t_env *e);
void				init_move(t_env *e);
void				init_env(t_env *e);

void				fill_steve(t_steve *steve);

int					loop_hook(t_env *e);
int					key_hook(int keycode, t_env *e);
int					key_hook_r(int keycode, t_env *e);

void				init_map(t_env *e);

void				move_right(t_env *e);
void				move_left(t_env *e);

int					main(void);
void				ft_error(char *s);

int					shoot(int button, int x, int y, t_env *e);

int					get_next_line(int fd, char **line);
int					my_read(int const fd, char **buf);
int					my_buf(char **buf, int *i, char **line);
char				*ft_strjoin(char const *s1, char const *s2);

#endif
