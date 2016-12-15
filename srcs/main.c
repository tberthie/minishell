/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 20:57:34 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 00:09:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <term.h>
#include <unistd.h>
#include <signal.h>

int			g_process = 0;

int			main(void)
{
	t_msh			*msh;
	char			*name;
	struct termios	term;

	signal(2, handler);
	if ((msh = setup()) &&
	(name = fetchenv(msh, "TERM")) &&
	tgetent(0, name) &&
	tcgetattr(0, &term) != -1)
	{
		term.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(0, TCSANOW, &term) != -1)
			input(msh);
	}
	else
		error("failed to load", 0);
	return (0);
}
