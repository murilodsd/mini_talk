/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:05:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/15 21:30:32 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_talk.h"

int	g_bit_received;

void	send_signal(int sig, pid_t pid)
{
	if (kill(pid, sig) == -1)
	{
		ft_printf(2, "Kill function failed");
		exit(EXIT_FAILURE);
	}
}

void	send_str_with_signal(int pid, char *str)
{
	int		j;
	int		i;
	char	*byte;

	j = 0;
	while (str[j])
	{
		byte = ft_char_to_byte(str[j]);
		i = 0;
		while (byte[i])
		{
			g_bit_received = 0;
			if (byte[i++] == '0')
				send_signal(SIGUSR1, pid);
			else
				send_signal(SIGUSR2, pid);
			while (!g_bit_received)
				;
			usleep(50);
		}
		free(byte);
		usleep(50);
		j++;
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
	if (signal(SIGUSR1, handler_sigusr) == SIG_ERR)
		exit(EXIT_FAILURE);
	send_str_with_signal(pid_server, argv[2]);
	ft_printf(1, "Mensagem recebida pelo processo pid %d\n", pid_server);
	return (0);
}
