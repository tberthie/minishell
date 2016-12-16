/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:32:09 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 14:40:13 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>

static int		parse_env(void)
{
	extern char		**environ;
	char			*tmp;
	int				pos;

	pos = 0;
	while (environ[pos])
	{
		tmp = ft_strdup(environ[pos]);
		if (!(g_msh->vals = tabinsert(g_msh->vals, ft_strchr(tmp, '=') + 1)))
			return (0);
		*(ft_strchr(tmp, '=')) = 0;
		if (!(g_msh->env = tabinsert(g_msh->env, tmp)))
			return (0);
		free(tmp);
		pos++;
	}
	return (1);
}

int				setup(void)
{
	if (!(g_msh = malloc(sizeof(t_msh))) ||
	!(g_msh->env = malloc(sizeof(char*))) ||
	!(g_msh->vals = malloc(sizeof(char*))) ||
	!(g_msh->history = malloc(sizeof(char*))))
		return (0);
	*g_msh->env = 0;
	*g_msh->vals = 0;
	*g_msh->history = 0;
	g_msh->proc = 0;
	return (!parse_env()) ? 0 : 1;
}
