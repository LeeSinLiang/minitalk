/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:00:51 by sinlee            #+#    #+#             */
/*   Updated: 2023/06/07 09:48:48 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_receive;

void	char_to_bin(char c, int pid)
{
	int	timer;
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		timer = -1;
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_receive == 0 && timer++)
		{
			if (timer == 50)
			{
				ft_printf("No response from server. :(");
				exit(1);
			}
			usleep(100);
		}
		g_receive = 0;
		bit_index--;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int					byte_index;
	int					pid;

	if (argc != 3)
	{
		ft_printf("2 arguments are required to run.");
		return (1);
	}
	byte_index = -1;
	pid = ft_atoi(argv[1]);
	while (argv[2][++byte_index])
		char_to_bin(argv[2][byte_index], pid);
	char_to_bin('\0', pid);
	return (0);
}
