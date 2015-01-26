/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 10:55:16 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/03 09:59:55 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_color(int r, int g, int b, t_color *get)
{
	get->r = r;
	get->g = g;
	get->b = b;
}

void	fill_steve(t_steve *steve)
{
	get_color(0, 255, 255, &(steve->north));
	get_color(255, 51, 0, &(steve->east));
	get_color(255, 255, 51, &(steve->south));
	get_color(153, 255, 0, &(steve->west));
}

void	init_draw(t_env *e)
{
	e->draw.camerax = 2 * e->draw.x / ((double)WIN_WIDTH) - 1;
	e->draw.ray_posx = e->posx;
	e->draw.ray_posy = e->posy;
	e->draw.ray_dirx = e->dirx + e->planex * e->draw.camerax;
	e->draw.ray_diry = e->diry + e->planey * e->draw.camerax;
	e->draw.mapx = ((int)e->draw.ray_posx);
	e->draw.mapy = ((int)e->draw.ray_posy);
	e->draw.delta_distx = sqrt(1 + (e->draw.ray_diry * e->draw.ray_diry) /
							(e->draw.ray_dirx * e->draw.ray_dirx));
	e->draw.delta_disty = sqrt(1 + (e->draw.ray_dirx * e->draw.ray_dirx) /
							(e->draw.ray_diry * e->draw.ray_diry));
	e->draw.hit = 0;
}

void	init_move(t_env *e)
{
	e->old_time = e->time;
	gettimeofday(&(e->move.time), NULL);
	e->move.usec = e->move.time.tv_usec;
	e->move.sec = e->move.time.tv_sec;
	e->time = ((e->move.sec) * 1000 + e->move.usec / 1000.0) + 0.5;
	e->frame_time = (e->time - e->old_time);
	e->move.movespeed = e->frame_time * 0.0035;
	e->move.rotspeed = e->frame_time * 0.0015;
}

void	init_env(t_env *e)
{
	e->inputs.up = 0;
	e->inputs.down = 0;
	e->inputs.right = 0;
	e->inputs.left = 0;
	e->img = NULL;
	e->posx = 20;
	e->posy = 20;
	e->dirx = -1;
	e->diry = 0;
	e->planex = 0;
	e->planey = 0.66;
}
