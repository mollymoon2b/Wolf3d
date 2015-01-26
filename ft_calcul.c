/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calcul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 10:54:23 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/02 13:37:28 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	calc_steps_and_side_dist(t_env *e)
{
	if (e->draw.ray_dirx < 0)
	{
		e->draw.stepx = -1;
		e->draw.side_distx = (e->draw.ray_posx - e->draw.mapx) *
			e->draw.delta_distx;
	}
	else
	{
		e->draw.stepx = 1;
		e->draw.side_distx = (e->draw.mapx + 1.0 - e->draw.ray_posx) *
			e->draw.delta_distx;
	}
	if (e->draw.ray_diry < 0)
	{
		e->draw.stepy = -1;
		e->draw.side_disty = (e->draw.ray_posy - e->draw.mapy) *
			e->draw.delta_disty;
	}
	else
	{
		e->draw.stepy = 1;
		e->draw.side_disty = (e->draw.mapy + 1.0 - e->draw.ray_posy) *
			e->draw.delta_disty;
	}
}

void	calc_wall_dist(t_env *e)
{
	if (e->draw.side == 0 || e->draw.side == 2)
		e->draw.perp_wall_dist = fabs((e->draw.mapx -
			e->draw.ray_posx + (1 - e->draw.stepx) / 2) / e->draw.ray_dirx);
	else
		e->draw.perp_wall_dist = fabs((e->draw.mapy -
			e->draw.ray_posy + (1 - e->draw.stepy) / 2) / e->draw.ray_diry);
}

void	calc_line_height(t_env *e)
{
	e->draw.line_height = fabs((int)(WIN_HEIGHT / e->draw.perp_wall_dist));
	e->draw.draw_start = -(e->draw.line_height) / 2 + WIN_HEIGHT / 2;
	if (e->draw.draw_start < 0)
		e->draw.draw_start = 0;
	e->draw.draw_end = e->draw.line_height / 2 + WIN_HEIGHT / 2;
	if (e->draw.draw_end >= WIN_HEIGHT)
		e->draw.draw_end = WIN_HEIGHT - 1;
	if (e->draw.side == 0)
		e->draw.c = e->s.north;
	else if (e->draw.side == 1)
		e->draw.c = e->s.south;
	else if (e->draw.side == 2)
		e->draw.c = e->s.east;
	else
		e->draw.c = e->s.west;
}
