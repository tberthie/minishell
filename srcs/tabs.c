/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 14:53:13 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 15:27:51 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

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

char		**tabpush(char **tab, char *line)
{
	char	**newtab;
	int		size;

	size = 0;
	while (tab[size])
		size++;
	if (!(newtab = malloc(sizeof(char*) * (size + 2))))
		return (0);
	newtab[size + 1] = 0;
	*newtab = ft_strdup(line);
	size = 0;
	while (tab[size++])
		newtab[size] = tab[size - 1];
	free(tab);
	return (newtab);
}

char		*addchar(char *str, char c)
{
	char	*new;
	int	i;

	i = ft_strlen(str) + 1;
	if (!(new = malloc(sizeof(char) * (i + 1))))
		return (0);
	new = ft_strcpy(new, str);
	new[i - 1] = c;
	new[i] = 0;
	free(str);
	return (new);
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

void		tabfree(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
