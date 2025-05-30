/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 07:59:32 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/04/24 00:11:50 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static int	g_ack = 0;

void	g_acknowledge(int sig)
{
	(void)sig;
	g_ack = 1;
}

void	send_signal(int pid, char *str)
{
	int				i;
	int				bit;
	unsigned char	c;

	i = 0;
	while (1)
	{
		c = str[i];
		bit = 8;
		while (bit--)
		{
			g_ack = 0;
			if ((c >> bit) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (g_ack != 1)
				usleep(1);
		}
		if (c == '\0')
			break ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [server PID] [message]\n");
		return (1);
	}
	sa.sa_handler = g_acknowledge;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	send_signal(ft_atoi(argv[1]), argv[2]);
	return (0);
}
