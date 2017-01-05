/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:24:37 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 15:34:01 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <term.h>

static void		move(char c)
{
	if (c == 'D' && g_msh->pos)
	{
		write(1, "\b", 1);
		g_msh->pos--;
	}
	else if (c == 'C' && g_msh->pos < g_msh->len)
	{
		write(1, &g_msh->line[g_msh->pos], 1);
		g_msh->pos++;
	}
}

static void		backspace(void)
{
	move('D');
	tputs(tgetstr("dc", 0), 0, put_ret);
	ft_strcpy(&g_msh->line[g_msh->pos], &g_msh->line[g_msh->pos + 1]);
	g_msh->len--;
}

static void		clear(void)
{
	tputs(tgetstr("cl", 0), 0, put_ret);
	prompt();
	write(1, g_msh->line, g_msh->len);
}

void			termcaps(char *tc)
{
	if (!tc)
		return ;
	*tc == 127 && g_msh->pos ? backspace() : 0;
	*tc == 27 ? move(tc[2]) : 0;
	*tc == 12 ? clear() : 0;
	free(tc);
}
