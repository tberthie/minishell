/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 23:12:43 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/12 23:14:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char			*fetchenv(t_msh *msh, char *name)
{
	int		pos;

	pos = 0;
	while (msh->env[pos])
	{
		if (!ft_strcmp(name, msh->env[pos]))
			return (msh->vals[pos]);
		pos++;
	}
	return (0);
}
