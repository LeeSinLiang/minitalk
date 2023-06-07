/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:00:51 by sinlee            #+#    #+#             */
/*   Updated: 2023/06/07 09:45:33 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_receive;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	i;

	(void)context;
	(void)info;
	(void)signum;
	g_receive = 1;
	if (signum == SIGUSR2)
		i++;
	else if (signum == SIGUSR1)
		ft_printf("Num of bytes received -> %d", i / 8);
}

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
	struct sigaction	sa;
	int					byte_index;
	int					pid;

	if (argc != 3)
	{
		ft_printf("2 arguments are required to run.");
		return (1);
	}
	byte_index = -1;
	pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error encountered. Exiting.\n");
		return (1);
	}
	ft_printf("Num of bytes sent -> %d\n", ft_strlen(argv[2]));
	while (argv[2][++byte_index])
		char_to_bin(argv[2][byte_index], pid);
	char_to_bin('\0', pid);
	return (0);
}
