/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:53:37 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 00:01:11 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

static void	exec_error(int id)
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

static char	*check_path(char *path, char *name)
{
	char			*tmp;
	char			*dir;

	if (!(dir = ft_strjoin(path, "/")) ||
	!(tmp = ft_strjoin(dir, name)))
		return (0);
	if (access(tmp, X_OK) != -1)
		return (tmp);
	return (0);
}

static char	*find_path(t_msh *msh, char *name)
{
	char	**paths;
	int		pos;
	char	*tmp;
	char	*path;

	pos = 0;
	if (!(tmp = fetchenv(msh, "PATH")))
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

int			execute(t_msh *msh, char **args)
{
	pid_t	childp;
	int		status;
	char	*path;

	if (!(path = find_path(msh, *args)))
		return (0);
	g_process = 1;
	childp = fork();
	if (childp < 0)
		error("fork failed", 0);
	else if (childp == 0)
	{
		execv(path, args);
		error("invalid command", *args);
		return (free_ret(path, 0));
	}
	else
	{
		wait(&status);
		exec_error(status);
	}
	g_process = 0;
	return (free_ret(path, 1));
}