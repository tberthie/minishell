/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 20:57:34 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/14 14:51:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <term.h>
#include <unistd.h>

int			main(void)
{
	t_msh			*msh;
	char			*name;
	struct termios	term;

	if ((msh = setup()) &&
	(name = fetchenv(msh, "TERM")) &&
	tgetent(0, name) &&
	tcgetattr(0, &term) != -1)
	{
		term.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(0, TCSANOW, &term) != -1)
			input(msh);
	}
	return (0);
}
