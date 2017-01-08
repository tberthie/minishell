/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:35:16 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/08 15:47:13 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void		echo(char **args)
{
	while (*args)
	{
		write(1, *args, ft_strlen(*args));
		if (*(++args))
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

char			*getword(char **line)
{
	char	*word;
	char	quote;

	if (!(word = malloc(sizeof(char))))
		return (0);
	*word = 0;
	while (**line && **line != ' ')
	{
		if (**line == '\'' || **line == '"')
		{
			quote = *((*line)++);
			while (**line && **line != quote)
				word = addchar(word, *((*line)++));
		}
		else
			word = addchar(word, **line);
		**line ? *line += 1 : 0;
	}
	return (word);
}

char			**split(char *line)
{
	char	**args;
	char	*word;

	if (!(args = malloc(sizeof(char*))))
		return (0);
	*args = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line)
		{
			if (!(word = getword(&line)) ||
			!(args = tabinsert(args, word)))
				return (0);
			free(word);
		}
	}
	return (args);
}

int				process(void)
{
	char	**args;

	if (!(args = split(g_msh->line)) || !*args)
		return (args) ? free_ret(args, 1) : 0;
	replace(&args[1]);
	if (!ft_strcmp(*args, "cd"))
		cd(args[1]);
	else if (!ft_strcmp(*args, "echo"))
		echo(&args[1]);
	else if (!ft_strcmp(*args, "env"))
		env();
	else if (!ft_strcmp(*args, "setenv"))
	{
		if (!set_env(args[1]))
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
