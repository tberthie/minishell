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
	write(1, "\x1b[31merror\x1b[0m: ", 17);
	write(1, msg, ft_strlen(msg));
	write(1, " \"", 2);
	str ? write(1, str, ft_strlen(str)) : 0;
	write(1, "\"\n", 2);
}
