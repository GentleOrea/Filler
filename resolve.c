/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 16:57:50 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/18 13:40:37 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int		add_value(t_global *g, int y, int x)
{
	if (y < 0 || x < 0 || y > (g->y - 1) || x > (g->x - 1))
		return (0);
	if (g->map[y][x] > (ft_abs(g->point.x - x) + ft_abs(g->point.y - y))
			|| !g->map[y][x])
	{
		if (g->map[y][x] >= 0)
			g->map[y][x] = ft_abs(g->point.x - x) + ft_abs(g->point.y - y);
		return (1);
	}
	return (0);
}

int		resolve(t_global *g, int y, int x)
{
	add_value(g, y - 1, x - 1) ? resolve(g, y - 1, x - 1) : 0;
	add_value(g, y - 1, x) ? resolve(g, y - 1, x) : 0;
	add_value(g, y - 1, x + 1) ? resolve(g, y - 1, x + 1) : 0;
	add_value(g, y, x + 1) ? resolve(g, y, x + 1) : 0;
	add_value(g, y + 1, x + 1) ? resolve(g, y + 1, x + 1) : 0;
	add_value(g, y + 1, x) ? resolve(g, y + 1, x) : 0;
	add_value(g, y + 1, x - 1) ? resolve(g, y + 1, x - 1) : 0;
	add_value(g, y, x - 1) ? resolve(g, y, x - 1) : 0;
	return (1);
}

int		browse_map(t_global *g, int mode, int y, int x)
{
	if (!g || mode == 2)
		return (0);
	if (x >= g->x && !(x = 0))
		y++;
	if (y >= g->y)
	{
		mode++;
		y = 0;
		x = 0;
	}
	if (!mode && g->map[y][x] == -1)
	{
		g->point.y = y;
		g->point.x = x;
		resolve(g, y, x);
	}
	else if (mode && !g->map[y][x])
		g->map[y][x] = (g->y * g->x);
	x++;
	browse_map(g, mode, y, x);
	return (1);
}

int		main(void)
{
	t_global	*global;
	char		*temp;

	if (!(global = init_global()))
		return (0);
	if (get_next_line(0, &temp) < 1 || !parse_player(temp, global))
	{
		erase_global(global);
		return (0);
	}
	while (1)
	{
		if (!parser(global))
		{
			erase_global(global);
			return (0);
		}
		browse_map(global, 0, 0, 0);
		pos_is_opti(global, 0, 0);
		free_piece(global);
		ft_printf("%d %d\n", global->result[0], global->result[1]);
	}
	return (0);
}
