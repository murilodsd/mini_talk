/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:05:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/06 18:49:47 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

extern int	g_bit_received;

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
	send_null_with_signal(pid_server);
	ft_printf(1, "Mensagem recebida pelo processo pid %d\n", pid_server);
	return (0);
}
