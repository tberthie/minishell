/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:11:21 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 14:53:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>

int			put_ret(int c)
{
	write(1, &c, 1);
	return (c);
}

int			free_ret(void *p, int ret)
{
	free(p);
	return (ret);
}

void		error(char *msg, char *str)
{
	if (str)
		ft_printf("{red}error{eoc}: %s \"%s\"\n", msg, str);
	else
		ft_printf("{red}error{eoc}: %s\n", msg);
}
