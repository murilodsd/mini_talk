/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:36:21 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/06 19:25:16 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char	*g_byte;

void	print_error_and_exit(char *error)
{
	ft_printf(2, "%s", error);
	exit(EXIT_FAILURE);
}

static void	handler_sigusr(int sig, siginfo_t *si, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
		*g_byte = '0';
	else
		*g_byte = '1';
	g_byte++;
	if (kill(si->si_pid, SIGUSR1) == -1)
		print_error_and_exit("kill function failed");
}

static void	get_bytes_print_string(void)
{
	char	*byte_start;
	int		i;

	byte_start = g_byte;
	while (1)
	{
		i = 8;
		while (i--)
			pause();
		g_byte = byte_start;
		if (ft_byte_to_char(byte_start) == 0)
			break ;
		ft_printf(1, "%c", ft_byte_to_char(byte_start));
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = handler_sigusr;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		print_error_and_exit("Sigaction failed");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		print_error_and_exit("Sigaction failed");
	g_byte = ft_calloc(9, sizeof(char));
	if (!g_byte)
		exit(EXIT_FAILURE);
	ft_printf(1, "SERVER PID: %d\n", getpid());
	while (1)
	{
		get_bytes_print_string();
		ft_printf(1, "\n");
	}
	free(g_byte);
	return (0);
}
