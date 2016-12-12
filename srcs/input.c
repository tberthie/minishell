/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:06:11 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/12 23:26:08 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>

void		input(t_msh *msh)
{
	char	*line;
	int		rd;

	line = 0;
	ft_printf("< {green}%s{eoc} > ", msh->user);
	while ((rd = ft_gnl(0, &line)))
	{
		if (rd == -1 || (*line && !process(msh, line)))
			return ;
		free(line);
		ft_printf("< {green}%s{eoc} > ", msh->user);
	}
}
