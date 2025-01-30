/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 12:35:14 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/01/30 12:35:14 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

volatile int	g_ack = 0;

void	ack_handler(int signum)
{
	(void)signum;
	g_ack = 1;
}

void	final_ack_handler(int signum)
{
	if (signum == SIGUSR2)
		write(1, "Message received by server!\n", 28);
}

void	send_signal(int pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_ack = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_ack)
			usleep(69);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int			i;
	pid_t		pid;
	const char	*str;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [STRING]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	signal(SIGUSR1, ack_handler);
	signal(SIGUSR2, final_ack_handler);
	i = 0;
	while (str[i])
		send_signal(pid, str[i++]);
	send_signal(pid, '\0');
	while (!g_ack)
		usleep(50);
	return (0);
}
