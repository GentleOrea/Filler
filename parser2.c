/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:39:17 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/18 13:47:35 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int		parse_piece(char *str, int i, t_global *global)
{
	int		x;
	int		ret;

	ret = 1;
	x = 0;
	while (ret && str[x])
	{
		if (x > global->point.x || !ft_isin(str[x], ".*"))
			ret = 0;
		else
			global->piece[i][x] = str[x];
		x++;
	}
	if (x != global->point.x)
		ret = 0;
	ft_memdel((void**)&str);
	return (ret);
}

int		parse_player(char *str, t_global *global)
{
	char	**tab;
	int		ret;

	ret = 1;
	if (ft_tablen(tab = ft_strsplit(str, ' ')) != 5 || ft_strcmp(tab[0], "$$$")
			|| ft_strcmp(tab[1], "exec") || tab[3][0] != ':'
			|| ft_strlen(tab[2]) != 2 || (tab[2][1] != '1' && tab[2][1] != '2'))
		ret = 0;
	else
		global->player = tab[2][1] - '0';
	ft_free_dblechar_tab(tab);
	ft_memdel((void**)&str);
	return (ret);
}
