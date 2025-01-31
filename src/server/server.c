/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 08:02:09 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/01/29 14:50:34 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void	handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 0;

	(void)context;
	if (signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		i = 0;
		c = 0;
	}
	usleep(1);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "Server is running...\n", 21);
	while (1)
		pause();
	return (0);
}
