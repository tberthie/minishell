/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 20:02:36 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 14:45:53 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <unistd.h>

void			handler(int sig)
{
	int		status;

	if (g_msh->proc)
	{
		waitpid(g_msh->proc, &status, 0);
		if (status == 2)
			write(1, "\n", 1);
	}
	else if (sig == 2)
	{
		write(1, "\n", 1);
		free(g_msh->line);
		g_msh->line = ft_strnew(0);
		g_msh->pos = 0;
		g_msh->len = 0;
		prompt();
	}
}
