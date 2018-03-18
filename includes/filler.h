/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:46:54 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/18 13:35:59 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
#include "../libft/includes/libft.h"

typedef struct s_point
{
	int		x;
	int		y;
	int		value;
	char	padding[4];
}				t_point;

typedef struct s_global
{
	t_point	point;
	int		fd;
	int		player;
	int		x;
	int		y;
	int		**map;
	char	**piece;
	int		result[2];
}		t_global;

int		ft_search_char(char *tab, char c, int end);
int		resolve(t_global *g, int y, int x);
int		browse_map(t_global *g, int mode, int y, int x);

void		erase_global(t_global *global);
t_global		*init_global(void);
int		add_value(t_global *global ,int y, int x);
int		calc_value(t_global *g, int y, int x);
void	pos_is_valid(t_global *g, int y, int x);
void	pos_is_opti(t_global *g, int y, int x);
int		parser(t_global *global);
int		parse_first_line(char *str, t_global *global);
int		parse_map(char *temp, t_global *global, int i);
int		parse_top_map(char *str, int length);
int		parse_att_piece(char *str, t_global *global);
int		parse_piece(char *str, int i, t_global *global);

int		parse_player(char *str, t_global *global);
void	free_piece(t_global *global);
#endif
