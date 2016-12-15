/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:32:09 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/15 22:50:35 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>

static int		parse_env(t_msh *msh)
{
	extern char		**environ;
	char			*tmp;
	int				pos;

	pos = 0;
	while (environ[pos])
	{
		tmp = ft_strdup(environ[pos]);
		if (!(msh->vals = tabinsert(msh->vals, ft_strchr(tmp, '=') + 1)))
			return (0);
		*(ft_strchr(tmp, '=')) = 0;
		if (!(msh->env = tabinsert(msh->env, tmp)))
			return (0);
		free(tmp);
		pos++;
	}
	return (1);
}

t_msh			*setup(void)
{
	t_msh			*msh;

	if (!(msh = malloc(sizeof(t_msh))) ||
	!(msh->env = malloc(sizeof(char*))) ||
	!(msh->vals = malloc(sizeof(char*))) ||
	!(msh->history = malloc(sizeof(char*))))
		return (0);
	*msh->env = 0;
	*msh->vals = 0;
	*msh->history = 0;
	return (!parse_env(msh) || !fetchenv(msh, "HOME") || !fetchenv(msh, "PWD")
	|| !fetchenv(msh, "OLDPWD")) ? 0 : msh;
}
