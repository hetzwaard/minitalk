/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 12:35:30 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/04/24 00:19:29 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static int	g_current_pid = 0;

void	print_char(unsigned char c)
{
	if (c == '\0')
		write(1, "\n", 1);
	else
		write(1, &c, 1);
}

void	handle_bit(int signal, siginfo_t *info, void *context)
{
	static int				bit_count = 0;
	static unsigned char	char_acc = 0;

	(void)context;
	if (g_current_pid == 0)
		g_current_pid = info->si_pid;
	if (info->si_pid != g_current_pid)
		return ;
	char_acc <<= 1;
	if (signal == SIGUSR2)
		char_acc |= 1;
	bit_count++;
	kill(g_current_pid, SIGUSR1);
	if (bit_count == 8)
	{
		print_char(char_acc);
		if (char_acc == '\0')
		{
			usleep(100);
			kill(g_current_pid, SIGUSR2);
			g_current_pid = 0;
		}
		bit_count = 0;
		char_acc = 0;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_bit;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Signal setup failed.\n");
		exit(1);
	}
}

int	main(void)
{
	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	setup_signals();
	while (1)
		pause();
	return (0);
}
