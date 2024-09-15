/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:36:21 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/15 21:28:46 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_talk.h"

char	*g_byte;

void	print_error_and_exit(char *error)
{
	free(g_byte);
	ft_printf(2, "%s", error);
	exit(EXIT_FAILURE);
}

/**
 * @brief Signal handler function for SIGINT.
 *
 * This function is responsible for handling the SIGINT signal. 
 * It frees the memory allocated for the variable g_byte
 * then sets the signal handler to the default behavior,
 * and sends the SIGINT signal to the current process.
 * So the program can exit in a clean way
 * @param sig The signal number.
 */
static void handler_sigint(int sig)
{
	free(g_byte);
	signal(sig, SIG_DFL);
	kill(SIGINT, getpid());
}

static void	handler_sigusr(int sig, siginfo_t *si, void *context)
{
	static int	i;
	
	(void)context;
	if (sig == SIGUSR1)
		*g_byte = '0';
	else
		*g_byte = '1';
	g_byte++;
	i++;
	if (i == 8)
	{
		g_byte = g_byte - 8;
		ft_printf(1, "%c", ft_byte_to_char(g_byte));
		i = 0;
	}
	if (kill(si->si_pid, SIGUSR1) == -1)
		print_error_and_exit("kill function failed");
}

static void	get_bytes_then_print_string(void)
{
	while (1)
		pause();
}

int	main(void)
{
	struct sigaction	sa;

	g_byte = ft_calloc(9, sizeof(char));
	if (!g_byte)
		exit(EXIT_FAILURE);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = handler_sigusr;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		print_error_and_exit("Sigaction failed");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		print_error_and_exit("Sigaction failed");
	if (signal(SIGINT, handler_sigint) == SIG_ERR)
		print_error_and_exit("Signal failed");
	ft_printf(1, "SERVER PID: %d\n", getpid());
	while (1)
	{
		get_bytes_then_print_string();
		ft_printf(1, "\n");
	}
	free(g_byte);
	return (0);
}
