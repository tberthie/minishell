/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:06:11 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/13 10:32:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>

void		input(t_msh *msh)
{
	char	c;
	int		rd;

	ft_printf("< {green}%s{eoc} > ", msh->user);
	while (1)
	{
		rd = read(0, &c, 1);
		write(1, &c, 1);
		/*if (rd == -1 || (*line && !process(msh, line)))
			return ;
		ft_printf("< {green}%s{eoc} > ", msh->user);*/
	}
}
