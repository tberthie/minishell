/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 20:02:36 by tberthie          #+#    #+#             */
/*   Updated: 2016/12/16 00:01:31 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <unistd.h>

void			handler(int sig)
{
	if (sig == 2)
	{
//		if (!g_process())
		write(1, "\n", 1);
	}
}
