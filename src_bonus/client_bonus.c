/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:05:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/17 19:37:47 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_talk.h"

int	g_bit_received;

/**
 * @brief Sends a signal to a specified process.
 *
 * This function attempts to send the specified signal
 * to the process with the given PID.
 * 
 * If the kill function fails,
 * an error message is printed and the function returns -1.
 *
 * @param sig The signal to be sent.
 * @param pid The process ID of the target process.
 * @return int Returns 0 on success, or -1 if the kill function fails.
 */
static int	send_signal(int sig, pid_t pid)
{
	if (kill(pid, sig) == -1)
	{
		ft_printf(2, "Kill function failed\n");
		return (-1);
	}
	return (0);
}

/**
 * @brief Fuction executed when there is an error.
 *
 * This function frees the memmory and exit
 * @param byte The memmory pointer to free.
 */
void	free_exit(char *byte)
{
	free(byte);
	exit(EXIT_FAILURE);
}

/**
 * @brief Sends a string to a process using signals.
 *
 * This function converts each character of the input string to its binary 
 * representation and sends it to the specified process using SIGUSR1 and 
 * SIGUSR2 signals.
 * 
 * SIGUSR1 when the bit is 0
 * SIGUSR2 when the bit is 1
 * 
 * It waits for an acknowledgment signal before sending 
 * the next bit.
 *
 * @param pid The process ID to which the signals will be sent.
 * @param str The string to be sent.
 *
 * @note The function uses a global variable `g_bit_received` to wait for 
 *       acknowledgment of each bit sent.
 * @note The function `ft_char_to_byte` is used to convert characters to 
 *       their binary representation.
 * @note The function `send_signal` is used to send signals to the process.
 * @note The function `free_exit` is called if the send_signal function fails.
 */
void	send_str_with_signal(int pid, char *str)
{
	int		j;
	int		i;
	int		check_return;
	char	*byte;

	j = 0;
	check_return = 0;
	while (str[j])
	{
		byte = ft_char_to_byte(str[j++]);
		i = 0;
		while (byte[i])
		{
			g_bit_received = 0;
			if (byte[i++] == '0')
				check_return = send_signal(SIGUSR1, pid);
			else
				check_return = send_signal(SIGUSR2, pid);
			if (check_return == -1)
				free_exit(byte);
			while (!g_bit_received)
				;
		}
		free(byte);
	}
}

/**
 * @brief Signal handler for SIGUSR1 and SIGUSR2 signals.
 *
 * This function is called when a SIGUSR1 or SIGUSR2 signal is received.
 * It sets the global variable `g_bit_received` to 1, indicating that
 * the server received the bit(signal).
 *
 * @param sig The signal number (unused in this handler).
 */
static void	handler_sigusr(int sig)
{
	(void)sig;
	g_bit_received = 1;
	return ;
}

/**
 * @brief Client program to send a message to a server process using signals.
 *
 * This program takes two arguments: 
 * the PID of the server process and the message to be sent.
 * 
 * It converts the PID from a string to an integer, sets up a signal handler,
 * and sends the message to the server process using signals.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int Returns 0 on successful execution.
 *
 * @note The program exits with EXIT_FAILURE
 * if the number of arguments is not equal to 3 or
 * if there is an error setting up the signal handler.
 */
int	main(int argc, char *argv[])
{
	int	pid_server;

	if (argc != 3)
	{
		ft_printf(2, "Error\nThis program takes two arguments\n");
		exit(EXIT_FAILURE);
	}
	if (!ft_isalldigits(argv[1]))
	{
		ft_printf(2, "Error\nThe first arg must be a positive number\n");
		exit(EXIT_FAILURE);
	}
	pid_server = ft_atoi(argv[1]);
	if (pid_server < 0)
		ft_printf(2, "The process doesn't exist\n");
	if (signal(SIGUSR1, handler_sigusr) == SIG_ERR)
		exit(EXIT_FAILURE);
	send_str_with_signal(pid_server, argv[2]);
	ft_printf(1, "Message received by the process pid %d\n", pid_server);
	return (0);
}
