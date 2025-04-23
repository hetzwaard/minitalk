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

static volatile sig_atomic_t	g_ack_received = 0;

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

void	send_char_bits(int pid, unsigned char c)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		g_ack_received = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_ack_received)
			usleep(100);
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

	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr("Client signal handler failed.\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (write(1, "Usage: ./client [PID] [MESSAGE]\n", 33), 1);
	pid = ft_atoi(argv[1]);
	if (pid <= MIN_PID || pid >= MAX_PID)
		return (write(1, "Error: Invalid PID.\n", 20), 1);
	setup_signal_handler();
	send_message(pid, argv[2]);
	return (0);
}
