/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 23:12:43 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 17:45:20 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char			*fetchenv(char *name)
{
	int		pos;

	pos = 0;
	while (g_msh->env[pos])
	{
		if (!ft_strcmp(name, g_msh->env[pos]))
			return (g_msh->vals[pos]);
		pos++;
	}
	return (0);
}

void			env(void)
{
	int		i;

	i = 0;
	while (g_msh->env[i])
	{
		ft_printf("%s=%s\n", g_msh->env[i], g_msh->vals[i]);
		i++;
	}
}

int				set_env(char *arg)
{
	char	*val;
	int		pos;

	pos = 0;
	if (!arg || !ft_strchr(arg, '='))
		error(arg ? "invalid value" : "invalid name", 0);
	else
	{
		if (!(val = ft_strdup(ft_strchr(arg, '=') + 1)))
			return (0);
		*ft_strchr(arg, '=') = 0;
		while (g_msh->env[pos])
			if (!ft_strcmp(g_msh->env[pos++], arg))
			{
				free(g_msh->vals[pos - 1]);
				g_msh->vals[pos - 1] = val;
				return (free_ret(arg, 1));
			}
		if (!(g_msh->env = tabinsert(g_msh->env, arg)) ||
		!(g_msh->vals = tabinsert(g_msh->vals, val)))
			return (0);
		free(val);
	}
	return (free_ret(arg, 1));
}

int				unset_env(char *arg)
{
	char	*val;
	int		pos;

	pos = 0;
	if (!arg)
		error("bad assignement", 0);
	else if (!(val = fetchenv(arg)))
		error("unknown value", arg);
	else
	{
		while (g_msh->env[pos])
		{
			if (!ft_strcmp(arg, g_msh->env[pos]))
			{
				tabremove(g_msh->env, g_msh->env[pos]);
				tabremove(g_msh->vals, g_msh->vals[pos]);
				return (1);
			}
			pos++;
		}
	}
	return (1);
}
