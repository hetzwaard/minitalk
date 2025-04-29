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

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				g_bit_count = 0;
	static unsigned char	g_char = 0;
	static pid_t			g_client_pid = 0;

	(void)context;
	if (g_client_pid == 0)
		g_client_pid = info->si_pid;
	g_char = g_char << 1;
	if (sig == SIGUSR2)
		g_char = g_char | 1;
	g_bit_count++;
	kill(g_client_pid, SIGUSR1);
	if (g_bit_count == 8)
	{
		write(1, &g_char, 1);
		if (g_char == '\0')
		{
			write(1, "\n", 1);
			g_client_pid = 0;
		}
		g_bit_count = 0;
		g_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
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