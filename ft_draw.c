/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 10:22:48 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/02 13:36:11 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pixel_to_img(t_env *e, int x, int y, t_color *c)
{
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;

	data = mlx_get_data_addr(e->img, &bpp, &sizeline, &endian);
	if (endian)
	{
		data[(y * sizeline) + x * (bpp / 8)] =
			mlx_get_color_value(e->mlx, c->r);
		data[(y * sizeline) + x * (bpp / 8) + 1] =
			mlx_get_color_value(e->mlx, c->g);
		data[(y * sizeline) + x * (bpp / 8) + 2] =
			mlx_get_color_value(e->mlx, c->b);
	}
	else
	{
		data[(y * sizeline) + x * (bpp / 8)] =
			mlx_get_color_value(e->mlx, c->b);
		data[(y * sizeline) + x * (bpp / 8) + 1] =
			mlx_get_color_value(e->mlx, c->g);
		data[(y * sizeline) + x * (bpp / 8) + 2] =
			mlx_get_color_value(e->mlx, c->r);
	}
}

void	vertical_line(t_env *e, int x, int start, int end)
{
	int		y;
	t_color	c2;

	y = 0;
	while (y < start)
	{
		get_color(255, 255, 255, &c2);
		put_pixel_to_img(e, x, y, &c2);
		y++;
	}
	while (start < end)
	{
		put_pixel_to_img(e, x, start, &(e->draw.c));
		start++;
	}
	while (start < MAP_HEIGHT)
	{
		get_color(0, 0, 0, &(e->draw.c));
		put_pixel_to_img(e, x, start, &(e->draw.c));
		start++;
	}
}

void	to_next_square(t_env *e)
{
	if (e->draw.side_distx < e->draw.side_disty)
	{
		e->draw.side_distx += e->draw.delta_distx;
		e->draw.mapx += e->draw.stepx;
		if (e->draw.stepx < 0)
			e->draw.side = 0;
		else
			e->draw.side = 2;
	}
	else
	{
		e->draw.side_disty += e->draw.delta_disty;
		e->draw.mapy += e->draw.stepy;
		if (e->draw.stepy < 0)
			e->draw.side = 1;
		else
			e->draw.side = 3;
	}
}

void	change_position(t_env *e)
{
	init_move(e);
	if (e->inputs.up)
	{
		if (e->world_map[(int)(e->posx + e->dirx * e->move.movespeed)]
			[(int)(e->posy)] == 0)
			e->posx += e->dirx * e->move.movespeed;
		if (e->world_map[(int)(e->posx)][(int)(e->posy + e->diry *
											e->move.movespeed)] == 0)
			e->posy += e->diry * e->move.movespeed;
	}
	if (e->inputs.down)
	{
		if (e->world_map[(int)(e->posx - e->dirx * e->move.movespeed)]
			[(int)(e->posy)] == 0)
			e->posx -= e->dirx * e->move.movespeed;
		if (e->world_map[(int)(e->posx)][(int)(e->posy - e->diry *
											e->move.movespeed)] == 0)
			e->posy -= e->diry * e->move.movespeed;
	}
	if (e->inputs.right)
		move_right(e);
	if (e->inputs.left)
		move_left(e);
}

void	ft_draw(t_env *e)
{
	e->img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->draw.x = 0;
	while (e->draw.x < WIN_WIDTH)
	{
		init_draw(e);
		calc_steps_and_side_dist(e);
		while (e->draw.hit == 0)
		{
			to_next_square(e);
			if (e->world_map[e->draw.mapx][e->draw.mapy] > 0)
				e->draw.hit = 1;
		}
		calc_wall_dist(e);
		calc_line_height(e);
		vertical_line(e, e->draw.x, e->draw.draw_start,
					e->draw.draw_end);
		e->draw.x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	change_position(e);
}
