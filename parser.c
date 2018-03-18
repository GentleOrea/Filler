/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 10:21:11 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/18 13:42:38 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int		parse_att_piece(char *str, t_global *global)
{
	char	**tab;
	int		ret;

	ret = 1;
	if (ft_tablen(tab = ft_strsplit(str, ' ')) != 3
		|| ft_strcmp(tab[0], "Piece") || !ft_atoi(tab[1]) || !ft_atoi(tab[2]))
		ret = 0;
	else
	{
		global->point.y = ft_atoi(tab[1]);
		global->point.x = ft_atoi(tab[2]);
	}
	ft_memdel((void**)&str);
	ft_free_dblechar_tab(tab);
	return (ret);
}

int		parse_top_map(char *str, int length)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (i != 4)
	{
		ft_memdel((void**)&str);
		return (0);
	}
	while (str[i] && str[i] == (((i - 4) % 10)) + '0' && (i - 4) != length)
		i++;
	ft_memdel((void**)&str);
	return ((i - 4) != length ? 0 : 1);
}

int		parse_map(char *temp, t_global *global, int i)
{
	int x;
	int ret;

	ret = 1;
	x = 4;
	ret = (ft_atoi(temp) != i || (temp[3] && temp[3] != ' ')) ? 0 : 1;
	while (ret && temp[x] && ft_isin(temp[x], ".oOxX"))
	{
		if ((x - 4) > global->x)
			ret = 0;
		else
		{
			if (temp[x] == '.')
				global->map[i][x - 4] = 0;
			else if (ft_isin(temp[x], "xX"))
				global->map[i][x - 4] = ((global->player == 1) ? -1 : -2);
			else
				global->map[i][x - 4] = ((global->player == 1) ? -2 : -1);
		}
		x++;
	}
	ret = (x != (global->x + 4)) ? 0 : 1;
	ft_memdel((void**)&temp);
	!ret ? ft_free_dblint_tab(global->map, (int)global->y) : 0;
	return (ret);
}

int		parse_first_line(char *str, t_global *global)
{
	char	**tab;
	int		ret;

	ret = 1;
	if (ft_tablen(tab = ft_strsplit(str, ' ')) != 3)
		ret = 0;
	if (ret && !global->x && ft_atoi(tab[1]) && ft_atoi(tab[2]))
	{
		global->y = ft_atoi(tab[1]);
		global->x = ft_atoi(tab[2]);
	}
	else if (!ret || !global->x || ((ft_strcmp(tab[0], "Plateau")
			|| ft_atoi(tab[1]) != global->y || ft_atoi(tab[2]) != global->x)))
		ret = 0;
	ft_free_dblechar_tab(tab);
	ft_memdel((void**)&str);
	return (ret);
}

int		parser(t_global *global)
{
	char	*temp;
	int		i;

	i = 0;
	if (get_next_line(0, &temp) < 1 || !parse_first_line(temp, global))
		return (0);
	if (get_next_line(0, &temp) < 1 || !parse_top_map(temp, global->x))
		return (0);
	if (!global->map
		&& !(global->map = ft_initdbl_int_tab((size_t)global->y,
				(size_t)global->x)))
		return (0);
	while (i < global->y && get_next_line(0, &temp) > 0)
		if (!parse_map(temp, global, i++))
			return (0);
	if (i != global->y || get_next_line(0, &temp) < 1
	|| !parse_att_piece(temp, global)
	|| !(global->piece = ft_init_double_tab(global->point.y, global->point.x)))
		return (0);
	i = 0;
	while (i < global->point.y && get_next_line(0, &temp) > 0)
		if (!parse_piece(temp, i++, global))
			return (0);
	return ((global->point.y == i) ? 1 : 0);
}
