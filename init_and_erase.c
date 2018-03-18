/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_erase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:33:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/18 13:44:01 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

t_global	*init_global(void)
{
	t_global *global;

	if (!(global = (t_global*)malloc(sizeof(t_global))))
		return (NULL);
	global->player = 0;
	global->x = 0;
	global->y = 0;
	global->map = NULL;
	global->point.y = 0;
	global->point.x = 0;
	global->point.value = -1;
	global->piece = NULL;
	global->result[0] = 0;
	global->result[1] = 0;
	return (global);
}

void		free_piece(t_global *global)
{
	int i;

	i = -1;
	if (global->piece)
	{
		while (global->piece[++i] && (i < global->y))
			ft_memdel((void**)&global->piece[i]);
		free(global->piece);
		global->piece = NULL;
	}
}

void		erase_global(t_global *global)
{
	if (!global)
		return ;
	ft_free_dblint_tab(global->map, global->y);
	free_piece(global);
	free(global);
	global = NULL;
}
