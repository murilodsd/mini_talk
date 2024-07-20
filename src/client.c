/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:05:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/07/18 22:04:11 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

int	count;

static void	handler_sigusr(int sig)
{
	(void)sig;
	return ;
}

int main(int argc, char *argv[])
{
	count = 0;
	if (argc != 3)
		exit(EXIT_FAILURE);
	if (signal(SIGUSR1, handler_sigusr) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
	ft_printf(1, "O PID É: %d\n",getpid());
	send_str_with_signal_sleep(ft_atoi(argv[1]), ft_itoa(getpid()), 2000);
	send_null_with_signal(ft_atoi(argv[1]));
	send_str_with_signal(ft_atoi(argv[1]), argv[2]);
	return 0;
}
