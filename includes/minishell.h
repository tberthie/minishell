/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:03:13 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/15 23:42:17 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "msh"

typedef struct		s_msh
{
	char			**env;
	char			**vals;
	char			**history;

	char			*line;
	int				pos;
	int				len;
}					t_msh;

extern int			g_process;

t_msh				*setup(void);
void				input(t_msh *msh);
int					process(t_msh *msh);
void				handler(int sig);

int					execute(t_msh *msh, char **args);
void				termcaps(t_msh *msh, char *tc);
char				*fetchenv(t_msh *msh, char *name);
void				env(t_msh *msh);
int					set_env(t_msh *msh, char *arg);
int					unset_env(t_msh *msh, char *arg);
void				prompt(t_msh *msh);

int					put_ret(int c);
int					free_ret(void *p, int ret);
void				error(char *msg, char *str);
char				**tabinsert(char **tab, char *line);
void				tabremove(char **tab, char *line);

#endif
