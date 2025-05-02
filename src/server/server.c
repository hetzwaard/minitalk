/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 08:02:09 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/04/24 00:12:20 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void	recieve_signal(int signal, siginfo_t *info, void *context)
{
	static int				bit_count = 0;
	static unsigned char	current_char = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	current_char = current_char << 1;
	if (signal == SIGUSR2)
		current_char = current_char | 1;
	bit_count++;
	kill(client_pid, SIGUSR1);
	if (bit_count == 8)
	{
		write(1, &current_char, 1);
		if (current_char == '\0')
		{
			write(1, "\n", 1);
			client_pid = 0;
		}
		bit_count = 0;
		current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = recieve_signal;
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
