/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 08:02:09 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/01/26 08:23:39 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	handler(int signal)
{
	static unsigned char	c = 0;
	static int				i = 0;

	if (signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			ft_printf("\n");
		}
		else
		{
			ft_printf("%c", c);
		}
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	write(1, "Server is running...\n", 21);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
