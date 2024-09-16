/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:05:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/16 22:10:14 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_talk.h"

int	g_bit_received;

static int	send_signal(int sig, pid_t pid)
{
	if (kill(pid, sig) == -1)
	{
		ft_printf(2, "Kill function failed\n");
		return (-1);
	}
	return (0);
}

void	free_exit(char *byte)
{
	free(byte);
	exit(EXIT_FAILURE);
}

void	send_str_with_signal(int pid, char *str)
{
	int		j;
	int		i;
	char	*byte;
	int	check_return;

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

static void	handler_sigusr(int sig)
{
	(void)sig;
	g_bit_received = 1;
	return ;
}

int	main(int argc, char *argv[])
{
	int	pid_server;

	if (argc != 3)
		exit(EXIT_FAILURE);
	pid_server = ft_atoi(argv[1]);
	if (pid_server < 0)
		ft_printf(2, "The process doesn't exist\n");
	if (signal(SIGUSR1, handler_sigusr) == SIG_ERR)
		exit(EXIT_FAILURE);
	send_str_with_signal(pid_server, argv[2]);
	ft_printf(1, "The message was received by the process pid %d\n", pid_server);
	return (0);
}
