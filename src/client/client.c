/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 07:59:32 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/01/30 11:12:43 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

volatile int	g_ack = 0;

void	ack_handler(int signum)
{
	(void)signum;
	g_ack = 1;
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
			usleep(1);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int			i;
	pid_t		pid;
	const char	*str;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [STRING]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	signal(SIGUSR1, ack_handler);
	while (str[i])
		send_signal(pid, str[i++]);
	send_signal(pid, '\0');
	return (0);
}
