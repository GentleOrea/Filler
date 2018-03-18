/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:44:33 by ygarrot           #+#    #+#             */
/*   Updated: 2017/12/06 18:59:27 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	size_t	i;
	void	*buf;

	buf = NULL;
	i = 0;
	if (size > 9223372036854775807)
		return (0);
	if (!(buf = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	while (i < size + 1)
	{
		((unsigned char*)buf)[i] = '\0';
		i++;
	}
	return (buf);
}
