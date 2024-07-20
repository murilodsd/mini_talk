/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:36:21 by mde-souz          #+#    #+#             */
/*   Updated: 2024/07/20 18:02:14 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

char	*byte;
int	count;

void	handler_sigusr(int sig)
{
	if (sig == SIGUSR1)
		*byte = '0';
	else
		*byte = '1';
}
void	get_bytes_print_string(int pid_client)
{
	char	*byte_start;
	int		i;
	
	count = 0;
	byte_start = byte;
	while (1)
	{		
		i = 8;
		while (i--)
		{
			pause();
			usleep(250);
			//ft_printf(1, "count = %d\n",++count);
			while (kill(pid_client, SIGUSR1) == -1)
				;
			byte++;
		}
		ft_printf(1, "%c", ft_byte_to_char(byte_start));
		byte = byte_start;
	}	
}

int main(void)
{
	
	char	*byte_start;
	int		pid_client;
	int		i;

	signal(SIGUSR1,handler_sigusr);
	signal(SIGUSR2,handler_sigusr);
	byte = ft_calloc(9, sizeof(char));
	if (!byte)
		exit(EXIT_FAILURE);
	ft_printf(1, "O PID É: %d",getpid());
	byte_start = byte;
	while (1)
	{
		ft_printf(1, "Primeiro programa sendo executado\n");
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
			ft_printf(1, "digito pid %d\n", (ft_byte_to_char(byte) - '0'));
			if (ft_byte_to_char(byte) == 0)
				break;
			pid_client = pid_client * 10 + (ft_byte_to_char(byte) - '0');
		}
		ft_printf(1, "Pid do programa sendo executado %d\n", pid_client);
		get_bytes_print_string(pid_client);	
	}
	return 0;
}
