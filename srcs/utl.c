/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:11:21 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/14 19:10:23 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void		prompt(t_msh *msh)
{
	ft_printf("< {green}%s{eoc} > ", msh->user);
}

int			put_ret(int c)
{
	write(1, &c, 1);
	return (c);
}

char		**insert(char **tab, char *line)
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
