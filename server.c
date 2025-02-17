/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:55:23 by luide-ca          #+#    #+#             */
/*   Updated: 2025/02/17 14:48:35 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_msg	g_to_print = {0, 0};

static void	join_msg(void)
{
	char	*msg;
	char	c;

	msg = NULL;
	c = g_to_print.c;
	if (g_to_print.msg != NULL)
	{
		msg = ft_strjoin(g_to_print.msg, &c);
		free(g_to_print.msg);
	}
	else
		msg = ft_strdup(&c);
	if (msg == NULL)
		exit (0);
	g_to_print.msg = msg;
}

static void	print_msg(void)
{
	if (g_to_print.c == '\0')
	{
		if (g_to_print.msg != NULL)
			ft_printf("%s\n", g_to_print.msg);
		else
			ft_printf("\n");
		free(g_to_print.msg);
		g_to_print.msg = NULL;
	}
	else
		join_msg();
	g_to_print.c = 0;
}
static void	handle_binary(int signal, siginfo_t *info, void *context)
{
	static int	count_bits = 0;

	(void)context;
	if (signal == SIGUSR1)
		g_to_print.c = (g_to_print.c << 1) | 1;
	else if (signal == SIGUSR2)
		g_to_print.c = (g_to_print.c << 1);
	count_bits++;
	if (count_bits == 8)
	{
		print_msg();
		count_bits = 0;
	}
	if (kill(info -> si_pid, SIGUSR1) == -1)
		exit(0);
}

static void	handle_binary(int signal, siginfo_t *info, void *context)
{
	static int	count_bits = 0;

	(void)context;
	if (signal == SIGUSR1)
		g_to_print.c = (g_to_print.c << 1) | 1;
	else if (signal == SIGUSR2)
		g_to_print.c = (g_to_print.c << 1);
	count_bits++;
	if (count_bits == 8)
	{
		print_msg();
		count_bits = 0;
	}
	if (kill(info -> si_pid, SIGUSR1) == -1)
		exit(0);
}

int	main(void)
{
	printf("Server (PID: %d)\n", getpid());
	sa.sa_sigaction = handle_binary;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (100)
		pause();
	return (0);
}