/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:36:21 by mde-souz          #+#    #+#             */
/*   Updated: 2024/07/22 22:01:44 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

char	*byte;

static void	handler_sigusr(int sig)
{
	if (sig == SIGUSR1)
		*byte = '0';
	else
		*byte = '1';
}
static void	get_bytes_print_string(int pid_client)
{
	char	*byte_start;
	int		i;
	
	byte_start = byte;
	while (1)
	{		
		i = 8;
		while (i)
		{
			if (i != 8)
				while (kill(pid_client, SIGUSR1) == -1)
					;
			pause();
			usleep(100);
			byte++;
			i--;
		}
		byte = byte_start;
		if (ft_byte_to_char(byte_start) == 0)
			break;
		ft_printf(1, "%c", ft_byte_to_char(byte_start));
		while (kill(pid_client, SIGUSR1) == -1)
			;
	}	
}

static int	get_pid_client(void)
{
	char	*byte_start;
	int		pid_client;
	int		i;
	
	byte_start = byte;
	pid_client = 0;
	while (1)
	{
		i = 8;
		while (i--)
		{
			pause();
			byte++;
		}
		byte = byte_start;
		if (ft_byte_to_char(byte) == 0)
			return (pid_client);
		pid_client = pid_client * 10 + (ft_byte_to_char(byte) - '0');
	}
}

int main(void)
{
	int		pid_client;

	signal(SIGUSR1,handler_sigusr);
	signal(SIGUSR2,handler_sigusr);
	byte = ft_calloc(9, sizeof(char));
	if (!byte)
		exit(EXIT_FAILURE);
	ft_printf(1, "SERVER PID: %d\n",getpid());
	while (1)
	{
		pid_client = get_pid_client();
		get_bytes_print_string(pid_client);
		while (kill(pid_client, SIGUSR1) == -1)
			;
		ft_printf(1,"\n");
	}
	free(byte);
	return 0;
}
