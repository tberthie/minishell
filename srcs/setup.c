/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:32:09 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/12 22:57:09 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>

static char		**insert(char **tab, char *line)
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

static int		setvars(t_msh *msh)
{
	int		pos;

	pos = 0;
	while (msh->env[pos])
	{
		if (!ft_strcmp(msh->env[pos], "HOME"))
			msh->home = msh->vals[pos];
		else if (!ft_strcmp(msh->env[pos], "PWD"))
			msh->pwd = msh->vals[pos];
		else if (!ft_strcmp(msh->env[pos], "OLDPWD"))
			msh->oldpwd = msh->vals[pos];
		else if (!ft_strcmp(msh->env[pos], "USER"))
			msh->user = msh->vals[pos];
		pos++;
	}
	return (!msh->home || !msh->pwd || !msh->oldpwd || !msh->user) ? 0 : 1;
}

t_msh			*setup(void)
{
	t_msh			*msh;
	extern char		**environ;
	char			*tmp;

	if (!(msh = malloc(sizeof(t_msh))) ||
	!(msh->env = malloc(sizeof(char*))) ||
	!(msh->vals = malloc(sizeof(char*))))
		return (0);
	*msh->env = 0;
	*msh->vals = 0;
	msh->pwd = 0;
	msh->oldpwd = 0;
	msh->home = 0;
	msh->user = 0;
	while (*environ)
	{
		tmp = ft_strchr(*environ, '=');
		*tmp = 0;
		if (!(msh->env = insert(msh->env, *environ)) ||
		!(msh->vals = insert(msh->vals, tmp + 1)))
			return (0);
		environ++;
	}
	return (setvars(msh)) ? msh : 0;
}
