/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 10:52:53 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/02 10:53:21 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_right(t_env *e)
{
	e->move.old_dirx = e->dirx;
	e->dirx = e->dirx * cos(-(e->move.rotspeed)) - e->diry *
		sin(-(e->move.rotspeed));
	e->diry = e->move.old_dirx * sin(-(e->move.rotspeed)) + e->diry *
		cos(-(e->move.rotspeed));
	e->move.old_planex = e->planex;
	e->planex = e->planex * cos(-(e->move.rotspeed)) - e->planey *
		sin(-(e->move.rotspeed));
	e->planey = e->move.old_planex * sin(-(e->move.rotspeed)) + e->planey *
		cos(-(e->move.rotspeed));
}

void	move_left(t_env *e)
{
	e->move.old_dirx = e->dirx;
	e->dirx = e->dirx * cos(e->move.rotspeed) - e->diry *
		sin(e->move.rotspeed);
	e->diry = e->move.old_dirx * sin(e->move.rotspeed) + e->diry *
		cos(e->move.rotspeed);
	e->move.old_planex = e->planex;
	e->planex = e->planex * cos(e->move.rotspeed) - e->planey *
		sin(e->move.rotspeed);
	e->planey = e->move.old_planex * sin(e->move.rotspeed) + e->planey *
		cos(e->move.rotspeed);
}
