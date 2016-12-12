/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:35:16 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/12 23:18:34 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void		test(t_msh *msh)
{
	int		i;

	i = 0;
	while (msh->env[i++])
		ft_printf("%s=%s\n", msh->env[i - 1], msh->vals[i - 1]);
}

int				process(t_msh *msh, char *line)
{
	if (!ft_strcmp(line, "env"))
		test(msh);
	return (1);
}
