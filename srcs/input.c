/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:06:11 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 16:31:40 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <term.h>

void			prompt(void)
{
	char	*user;

	(user = fetchenv("USER")) ? ft_printf("< {green}%s{eoc} > ", user) :
	ft_printf("< {green}%s{eoc} > ", PROMPT);
}

static int		exec(void)
{
	if (g_msh->pos != g_msh->len)
		write(1, &g_msh->line[g_msh->pos], ft_strlen(&g_msh->line[g_msh->pos]));
	write(1, "\n", 1);
	if (*g_msh->line && !process())
		return (0);
	free(g_msh->line);
	g_msh->line = ft_strnew(0);
	g_msh->pos = 0;
	g_msh->len = 0;
	prompt();
	return (1);
}

static int		addbuff(char *buff)
{
	char	*tmp;
	int		i;

	if (g_msh->pos < g_msh->len)
	{
		if (!(tmp = ft_strndup(g_msh->line, ft_strlen(g_msh->line) + 1)))
			return (0);
		tmp[g_msh->pos] = *buff;
		ft_strcpy(&tmp[g_msh->pos + 1], &g_msh->line[g_msh->pos]);
	}
	else if (!(tmp = ft_strjoin(g_msh->line, buff)))
		return (0);
	i = ft_strlen(&tmp[g_msh->pos]);
	write(1, &tmp[g_msh->pos], i);
	while (--i)
		write(1, "\b", 1);
	free(g_msh->line);
	g_msh->line = tmp;
	g_msh->len++;
	g_msh->pos++;
	return (1);
}

void			input(void)
{
	char	buff[4];
	int		rd;

	g_msh->line = ft_strnew(0);
	g_msh->pos = 0;
	g_msh->len = 0;
	prompt();
	while ((rd = read(0, buff, 3)))
	{
		buff[rd] = 0;
		if (*buff == '\n' && !exec())
			return ;
		else if (*buff < 32 || *buff == 127)
			termcaps(ft_strdup(buff));
		else if (*buff > 31 && !addbuff(buff))
			return ;
	}
}
