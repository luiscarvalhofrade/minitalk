/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:55:26 by luide-ca          #+#    #+#             */
/*   Updated: 2025/02/17 14:42:42 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_flag = 0;

void	handle_sigint(int sig)
{
	if (sig == SIGUSR1)
		g_flag = 1;
}

static void	send_msg(int pid, char *msg)
{
	int	bit_index;
	int	char_index;
	int	len;

	char_index = 0;
	len = ft_strlen(msg);
	while (char_index <= len)
	{
		bit_index = 7;
		while (bit_index >= 0)
		{
			if ((msg[char_index] >> bit_index) & 1)
				kill (pid, SIGUSR1);
			else
				kill (pid, SIGUSR2);
			bit_index--;
			while (g_flag == 0)
				usleep(1000);
			g_flag = 0;
		}
		char_index++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Execute client as follows: ./client [PID] [message]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, handle_sigint);
	send_msg(pid, argv[2]);
	return (0);
}