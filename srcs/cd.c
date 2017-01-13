/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:38:17 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/13 13:24:12 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <limits.h>

void		cd(char *path)
{
	char	buff[PATH_MAX];
	char	*env;
	char	*tmp;

	if (!path || !ft_strcmp(path, "~") || !ft_strcmp(path, "-"))
		path = path && (*path == '-') ? fetchenv("OLDPWD") : fetchenv("HOME");
	if (!path || (chdir(path) == -1))
		return (error("invalid path", path));
	tmp = fetchenv("PWD");
	if (!(env = ft_strjoin("PWD=", getcwd(buff, PATH_MAX))) || !set_env(env))
		return ;
	free(env);
	if (tmp && *tmp)
	{
		if (!(env = ft_strjoin("OLDPWD=", tmp)) || !set_env(env))
			return ;
		free(env);
	}
}
