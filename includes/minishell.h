/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:03:13 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/14 19:10:28 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct		s_msh
{
	char	**env;
	char	**vals;
	char	**history;

	char	*pwd;
	char	*oldpwd;
	char	*home;
	char	*user;

	char	*line;
	int		pos;
	int		len;
}					t_msh;

t_msh				*setup(void);
void				input(t_msh *msh);
int					process(t_msh *msh, char *line);

void				termcaps(t_msh *msh, char *tc);
void				arrow(t_msh *msh, char c);

char				*fetchenv(t_msh *msh, char *name);

int					put_ret(int c);
void				prompt(t_msh *msh);
char				**insert(char **tab, char *line);

#endif
