/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 23:12:43 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/15 21:52:06 by tberthie         ###   ########.fr       */
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

void			env(t_msh *msh)
{
	int		i;

	i = 0;
	while (msh->env[i])
	{
		ft_printf("%s=%s\n", msh->env[i], msh->vals[i]);
		i++;
	}
}

int				set_env(t_msh *msh, char *arg)
{
	char	*env;
	char	*val;
	int		pos;

	pos = 0;
	if (!arg || !ft_strchr(arg, '='))
		error(arg ? "invalid value" : "invalid name", 0);
	else
	{
		if (!(env = ft_strdup(arg)) ||
		!(val = ft_strdup(ft_strchr(arg, '=') + 1)))
			return (0);
		*ft_strchr(env, '=') = 0;
		while (msh->env[pos])
			if (!ft_strcmp(msh->env[pos++], env))
			{
				free(msh->vals[pos - 1]);
				msh->vals[pos - 1] = val;
				free(env);
				return (1);
			}
		return (!(msh->env = tabinsert(msh->env, env)) ||
		!(msh->vals = tabinsert(msh->vals, val))) ? 0 : 1;
	}
	return (1);
}

int				unset_env(t_msh *msh, char *arg)
{
	char	*val;
	int		pos;

	pos = 0;
	if (!arg)
		error("bad assignement", 0);
	else if (!(val = fetchenv(msh, arg)))
		error("unknown value", arg);
	else
	{
		while (msh->env[pos])
		{
			if (!ft_strcmp(arg, msh->env[pos]))
			{
				tabremove(msh->env, msh->env[pos]);
				tabremove(msh->vals, msh->vals[pos]);
				return (1);
			}
			pos++;
		}
	}
	return (1);
}
