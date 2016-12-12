/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:03:13 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/12 23:12:32 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct		s_msh
{
	char	**env;
	char	**vals;

	char	*pwd;
	char	*oldpwd;
	char	*home;

	char	*user;
}					t_msh;

t_msh				*setup(void);
void				input(t_msh *msh);
int					process(t_msh *msh, char *line);

char				*fetchenv(t_msh *msh, char *name);

#endif
