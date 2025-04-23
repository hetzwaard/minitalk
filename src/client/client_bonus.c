/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 12:35:14 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/04/24 00:20:45 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static volatile sig_atomic_t	g_ack = 0;

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
		g_ack = 2;
}

void	send_char_bits(int pid, unsigned char c)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		g_ack = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (g_ack != 1)
			usleep(50);
	}
}

void	send_message(int pid, const char *msg)
{
	int	i;

	i = 0;
	while (1)
	{
		send_char_bits(pid, msg[i]);
		if (msg[i] == '\0')
			break ;
		i++;
	}
}

void	setup_signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Client signal handler failed.\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (write(1, "Usage: ./client_bonus [PID] [MESSAGE]\n", 39), 1);
	pid = ft_atoi(argv[1]);
	setup_signal_handler();
	send_message(pid, argv[2]);
	while (g_ack != 2)
		usleep(50);
	ft_putstr("Mission accomplished.\n");
	return (0);
}
