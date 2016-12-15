/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:11:21 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/15 23:30:37 by tberthie         ###   ########.fr       */
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
		ft_printf("{red}error{eoc}: > %s \"%s\"\n", msg, str);
	else
		ft_printf("{red}error{eoc} > %s\n", msg);
}

char		**tabinsert(char **tab, char *line)
{
	char	**newtab;
	int		size;

	size = 0;
	while (tab[size])
		size++;
	if (!(newtab = malloc(sizeof(char*) * (size + 2))))
		return (0);
	newtab[size + 1] = 0;
	newtab[size] = ft_strdup(line);
	while (size--)
		newtab[size] = tab[size];
	free(tab);
	return (newtab);
}

void		tabremove(char **tab, char *line)
{
	int		size;

	size = 0;
	while (tab[size] != line)
		size++;
	free(tab[size++]);
	while (tab[size])
	{
		tab[size - 1] = tab[size];
		size++;
	}
	tab[size - 1] = 0;
}
