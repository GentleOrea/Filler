/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:41:49 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/18 11:28:07 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int		calc_value(t_global *g, int y, int x)
{
	int px;
	int py;
	int value;
	int stop;

	stop = 0;
	value = 0;
	py = -1;
	while (g->piece[++py])
	{
		px = -1;
		while (g->piece[py][++px])
			if (g->piece[py][px] == '*')
			{
				if ((g->point.x + px - x) < 0 || (g->point.y + py - y) < 0
	|| (g->point.x + px - x) > (g->x - 1) || (g->point.y + py - y) > (g->y - 1)
	|| g->map[g->point.y + py - y][g->point.x + px - x] == -1)
					return (-1);
				if (g->map[g->point.y + py - y][g->point.x + px - x] == -2)
					stop++;
				else
					value += g->map[g->point.y + py - y][g->point.x + px - x];
			}
	}
	return ((stop == 1) ? value : -1);
}

void	pos_is_valid(t_global *g, int y, int x)
{
	int value;

	if (!g->piece[y][x] && !(x = 0))
		y++;
	if (!g->piece[y])
		return ;
	value = -1;
	if (g->piece[y][x] == '*')
		value = calc_value(g, y, x);
	if (value >= 0 && (g->point.value < 0 || g->point.value > value))
	{
		g->point.value = value;
		g->result[0] = g->point.y - y;
		g->result[1] = g->point.x - x;
	}
	x++;
	pos_is_valid(g, y, x);
}

void	pos_is_opti(t_global *g, int y, int x)
{
	if (!y && !x)
	{
		g->result[0] = 0;
		g->result[1] = 0;
		g->point.value = -1;
	}
	if (x >= g->x && !(x = 0))
		y++;
	if (y >= g->y)
		return ;
	if (g->map[y][x] == -2)
	{
		g->point.x = x;
		g->point.y = y;
		pos_is_valid(g, 0, 0);
	}
	x++;
	pos_is_opti(g, y, x);
}
