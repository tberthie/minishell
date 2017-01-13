/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:03:13 by tberthie          #+#    #+#             */
/*   Updated: 2017/01/09 13:52:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "msh"

typedef struct		s_msh
{
	char			**env;
	char			**vals;

	char			*line;
	int				pos;
	int				len;

	int				proc;
}					t_msh;

t_msh				*g_msh;

int					setup(void);
void				input();
int					process();
void				handler(int sig);

void				cd(char *path);
int					execute(char **args);
void				termcaps(char *tc);
char				*fetchenv(char *name);
void				env();
int					set_env(char *arg);
int					unset_env(char *arg);
void				prompt();

int					put_ret(int c);
int					free_ret(void *p, int ret);
void				error(char *msg, char *str);
char				**tabinsert(char **tab, char *line);
char				**tabpush(char **tab, char *line);
void				tabremove(char **tab, char *line);
void				tabfree(char **tab);
char				*addchar(char *str, char c);

#endif
