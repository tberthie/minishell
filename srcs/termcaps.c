/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:24:37 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/15 21:54:40 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <term.h>

static void		move(t_msh *msh, char c)
{
	char	*res;

	res = 0;
	if (c == 'D' && msh->pos)
	{
		write(1, "\b", 1);
		msh->pos--;
	}
	else if (c == 'C' && msh->pos < msh->len)
	{
		write(1, &msh->line[msh->pos], 1);
		msh->pos++;
	}
}

static void		backspace(t_msh *msh)
{
	move(msh, 'D');
	tputs(tgetstr("dc", 0), 0, put_ret);
	ft_strcpy(&msh->line[msh->pos], &msh->line[msh->pos + 1]);
	msh->len--;
}

static void		clear(t_msh *msh)
{
	tputs(tgetstr("cl", 0), 0, put_ret);
	prompt(msh);
	write(1, msh->line, msh->len);
}

void			termcaps(t_msh *msh, char *tc)
{
	if (!tc)
		return ;
	*tc == 127 && msh->pos ? backspace(msh) : 0;
	*tc == 27 ? move(msh, tc[2]) : 0;
	*tc == 12 ? clear(msh) : 0;
	free(tc);
}
