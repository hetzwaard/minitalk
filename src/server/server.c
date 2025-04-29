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

void	receive_signal(int signal)
{
	static int	bit_count = 0;
	static char	current_char = 0;

	if (signal == SIGUSR1 || signal == SIGUSR2)
	{
		if (signal == SIGUSR1)
			current_char = current_char << 1;
		else if (signal == SIGUSR2)
			current_char = (current_char << 1) | 1;
		bit_count++;
		if (bit_count == 8)
		{
			write(1, &current_char, 1);
			current_char = 0;
			bit_count = 0;
		}
	}
	
}

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	signal(SIGUSR1, receive_signal);
	signal(SIGUSR2, receive_signal);
	while (1)
		pause();
	return (0);
}