/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:53:37 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/08 14:31:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

static void		exec_error(int id)
{
	if (id == 6)
		ft_printf("{red}error{eoc} > process terminated [ABRT]\n");
	else if (id == 8)
		ft_printf("{red}error{eoc} > process terminated [FPE]\n");
	else if (id == 10)
		ft_printf("{red}error{eoc} > process terminated [BUSERR]\n");
	else if (id == 11)
		ft_printf("{red}error{eoc} > process terminated [SEGV]\n");
}

static char		*check_path(char *path, char *name)
{
	char			*tmp;
	char			*dir;

	if (!(dir = ft_strjoin(path, "/")) ||
	!(tmp = ft_strjoin(dir, name)))
		return (0);
	free(dir);
	if (access(tmp, X_OK) != -1)
		return (tmp);
	free(tmp);
	return (0);
}

static char		*find_path(char *name)
{
	char	**paths;
	int		pos;
	char	*tmp;
	char	*path;

	pos = 0;
	if (!(tmp = fetchenv("PATH")))
		return (ft_strdup(name));
	if (!(paths = ft_strsplit(tmp, ':')))
		return (0);
	path = 0;
	while (paths[pos])
	{
		!path ? path = check_path(paths[pos], name) : 0;
		free(paths[pos++]);
	}
	free(paths);
	return (path ? path : ft_strdup(name));
}

static char		**buildenv(void)
{
	char	**tab;
	char	*tmp;
	char	*env;
	int		pos;

	pos = 0;
	if (!(tab = malloc(sizeof(char*))))
		return (0);
	*tab = 0;
	while (g_msh->env[pos])
	{
		tmp = ft_strjoin(g_msh->env[pos], "=");
		env = ft_strjoin(tmp, g_msh->vals[pos]);
		free(tmp);
		if (!(tab = tabinsert(tab, env)))
			return (0);
		free(env);
		pos++;
	}
	tab[pos] = 0;
	return (tab);
}

int				execute(char **args)
{
	pid_t	childp;
	int		status;
	char	*path;

	if (!(path = find_path(*args)))
		return (0);
	childp = fork();
	g_msh->proc = childp;
	if (childp < 0)
		error("fork failed", 0);
	else if (childp == 0)
	{
		execve(path, args, buildenv());
		error("invalid/forbidden command", *args);
		return (free_ret(path, 0));
	}
	else
	{
		wait(&status);
		exec_error(status);
	}
	g_msh->proc = 0;
	return (free_ret(path, 1));
}
