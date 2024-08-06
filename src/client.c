/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:05:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/05 18:21:39 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

extern int g_bit_received;

static void	handler_sigusr(int sig)
{
	(void)sig;
	g_bit_received = 1;
	return ;
}

int main(int argc, char *argv[])
{
	int	pid_server;
	
	pid_server = ft_atoi(argv[1]);
	if (argc != 3)
		exit(EXIT_FAILURE);
	if (signal(SIGUSR1, handler_sigusr) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
	send_str_with_signal_sleep(pid_server, ft_itoa(getpid()), 4000);
	send_null_with_signal(pid_server);
	send_str_with_signal(pid_server, argv[2]);
	send_null_with_signal(pid_server);
	ft_printf(1, "Mensagem recebida com sucesso pelo processo pid %d\n",pid_server);
	return 0;
}
