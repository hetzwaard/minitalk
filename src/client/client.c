/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 07:59:32 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/01/26 08:23:18 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	send_signal(int pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int			i;
	const char	*str;
	pid_t		pid;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [STRING]\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	while (str[i])
		send_signal(pid, str[i++]);
	send_signal(pid, '\0');
	return (0);
}
