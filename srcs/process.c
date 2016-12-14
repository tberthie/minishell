/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:35:16 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/14 17:46:53 by tberthie         ###   ########.fr       */
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
	char	**args;

	if (!(args = ft_strsplit(line, ' ')))
		return (0);
	if (!ft_strcmp(*args, "env"))
		test(msh);
	else if (!ft_strcmp(*args, "exit"))
		return (0);
	else if (*args)
	{
		if (ft_strlen(*args) > 23)
		   	ft_strcpy(&(*args)[20], "...\0");
		ft_printf("{red}error{eoc} > invalid command %s\n", *args);
	}
	return (1);
}
