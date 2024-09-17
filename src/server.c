/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:36:21 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/17 10:49:09 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_talk.h"

/**
 * A global pointer to a dynamically allocated memory
 * used to receive the char binary.
 */
static char	*g_byte;

/**
 * @brief Fuction executed when there is an error.
 *
 * This function frees the global pointer memmory,
 * prints the error message and exits the program.
 * @param error The error message.
 */
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
static void	handler_sigint(int sig)
{
	struct sigaction	sa;

	(void)sig;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		print_error_and_exit("Failed to set SIGINT to default behavior");
	if (g_byte)
	{
		free(g_byte);
		g_byte = NULL;
	}
	if (kill(getpid(), SIGINT) == -1)
		print_error_and_exit("kill function failed");
}

/**
 * @brief Signal handler function for SIGUSR1 and SIGUSR2 signals,
 * that receive and print the data that was sent.
 * 
 * This function is responsible for handling the SIGUSR1 and SIGUSR2 signals.
 * It updates the value of the global variable `g_byte` represents
 * the binary of a number from the ASCII table that is being received by the server.
 * If the signal is SIGUSR1, the value of `g_byte` is set to '0'.
 * If the signal is SIGUSR2, the value of `g_byte` is set to '1'.
 * 
 * When all the 8 bits are received, the function converts the byte to a character
 * using the `ft_byte_to_char` function, prints it and sends a SIGUSR1 signal back 
 * to the process that sent the signal using the `kill` function.
 * 
 * @param sig The signal number.
 * @param si A pointer to a siginfo_t structure containing information about the signal.
 * @param context A pointer to a ucontext_t structure containing the signal context.
 */
static void	handler_sigusr(int sig, siginfo_t *si, void *context)
{
	static int count;

	(void)context;
	if (sig == SIGUSR1)
		*g_byte = '0';
	else
		*g_byte = '1';
	g_byte++;
	count++;
	if (count == 8)
	{
		g_byte = g_byte - 8;
		ft_printf(1, "%c", ft_byte_to_char(g_byte));
		count = 0;
	}
	if (kill(si->si_pid, SIGUSR1) == -1)
		print_error_and_exit("kill function failed");
}

/**
 * @brief Server program for handling signals.
 *
 * This program sets up signal handlers for SIGUSR1, SIGUSR2, and SIGINT signals.
 * 
 * The entry point of the server program. It initializes signal handlers and enters an infinite loop.
 *
 * Signal Handlers:
 * - handler_sigusr: Function to handle SIGUSR1 and SIGUSR2 signals.
 * - handler_sigint: Function to handle SIGINT signal.
 */
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
		pause();
	free(g_byte);
	return (0);
}
