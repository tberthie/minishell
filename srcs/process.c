/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:35:16 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 17:45:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void		echo(char *line)
{
	while (*line != 'e')
		line++;
	line += 4;
	while (*line == ' ')
		line++;
	while (*line)
	{
		while (*line && *line != ' ')
		{
			if (*line == '"' && (line += 1))
				while (*line && *line != '"')
					write(1, line++, 1);
			else if (*line == '\'' && (line += 1))
				while (*line && *line != '\'')
					write(1, line++, 1);
			else
				write(1, line, 1);
			*line ? line += 1 : 0;
		}
		while (*line == ' ')
			line++;
		if (*line)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

static void		replace(char **args)
{
	char	*tmp;

	if (!(tmp = fetchenv("HOME")))
		return ;
	while (*args)
	{
		if (!ft_strcmp(*args, "~"))
		{
			free(*args);
			*args = ft_strdup(tmp);
		}
		args++;
	}
}

int				process(void)
{
	char	**args;

	if (!(args = ft_strsplit(g_msh->line, ' ')) || !*args)
		return (args) ? free_ret(args, 1) : 0;
	replace(&args[1]);
	if (!ft_strcmp(*args, "cd"))
		cd(args[1]);
	else if (!ft_strcmp(*args, "echo"))
		echo(g_msh->line);
	else if (!ft_strcmp(*args, "env"))
		env();
	else if (!ft_strcmp(*args, "setenv"))
	{
		if (!set_env(ft_strdup(args[1])))
			return (0);
	}
	else if (!ft_strcmp(*args, "unsetenv"))
	{
		if (!unset_env(args[1]))
			return (0);
	}
	else if (!ft_strcmp(*args, "exit") || !execute(args))
		return (0);
	tabfree(args);
	return (1);
}
