/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:06:11 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/14 19:14:49 by tberthie         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <term.h>

static int		exec(t_msh *msh)
{
	if (msh->pos != msh->len)
		write(1, &msh->line[msh->pos], ft_strlen(&msh->line[msh->pos]));
	write(1, "\n", 1);
	if (*msh->line && !process(msh, msh->line))
		return (0);
	free(msh->line);
	msh->line = ft_strnew(0);
	msh->pos = 0;
	msh->len = 0;
	prompt(msh);
	return (1);
}

static int		addbuff(t_msh *msh, char *buff)
{
	char	*tmp;
	int		i;

	if (msh->pos < msh->len)
	{
		if (!(tmp = ft_strndup(msh->line, ft_strlen(msh->line) + 1)))
			return (0);
		tmp[msh->pos] = *buff;
		ft_strcpy(&tmp[msh->pos + 1], &msh->line[msh->pos]);
	}
	else if (!(tmp = ft_strjoin(msh->line, buff)))
			return (0);
	i = ft_strlen(&tmp[msh->pos]);
	write(1, &tmp[msh->pos], i);
	while (--i)
		write(1, "\b", 1);
	free(msh->line);
	msh->line = tmp;
	msh->len++;
	msh->pos++;
	return (1);
}

void			input(t_msh *msh)
{
	char	buff[4];
	int		rd;

	msh->line = ft_strnew(0);
	msh->pos = 0;
	msh->len = 0;
	prompt(msh);
	while ((rd = read(0, buff, 3)))
	{
		buff[rd] = 0;
		if (*buff == '\n' && !exec(msh))
			return ;
		else if (*buff < 32 || *buff == 127)
			termcaps(msh, ft_strdup(buff));
		else if (*buff > 31 && !addbuff(msh, buff))
			return ;
	}
}
