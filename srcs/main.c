/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 20:57:34 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 14:14:06 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <term.h>
#include <unistd.h>
#include <signal.h>

int			main(void)
{
	char			*name;
	struct termios	term;

	signal(2, handler);
	if ((setup()) &&
	(name = fetchenv("TERM")) &&
	tgetent(0, name) &&
	tcgetattr(0, &term) != -1)
	{
		term.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(0, TCSANOW, &term) != -1)
			input();
	}
	else
		error("failed to load", 0);
	return (0);
}
