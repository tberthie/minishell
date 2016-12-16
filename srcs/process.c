/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:35:16 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 14:39:39 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void			echo(char *line)
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

int				process(void)
{
	char	**args;
	int		i;

	i = 0;
	if (!(args = ft_strsplit(g_msh->line, ' ')))
		return (0);
	if (*args)
	{
		if (!ft_strcmp(*args, "env"))
			env();
		else if (!ft_strcmp(*args, "echo"))
			echo(g_msh->line);
		else if (!ft_strcmp(*args, "setenv"))
			return (set_env(args[1]));
		else if (!ft_strcmp(*args, "unsetenv"))
			return (unset_env(args[1]));
		else if (!ft_strcmp(*args, "exit") || !execute(args))
			return (0);
	}
	while (args[i])
		free(args[i++]);
	free(args);
	return (1);
}
