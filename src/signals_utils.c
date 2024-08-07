/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:12 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/06 20:10:58 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

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
			usleep(20000);
		}
		free(byte);
		usleep(20000);
		j++;
	}
}

void	send_str_with_signal_sleep(int pid, char *str, int usec)
{
	int		j;
	char	*byte;

	j = 0;
	while (str[j])
	{
		byte = ft_char_to_byte(str[j]);
		while (*byte)
		{
			if (*byte++ == '0')
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(usec);
		}
		j++;
	}
}

void	send_null_with_signal(int pid)
{
	int	j;

	j = 8;
	while (j--)
	{
		kill(pid, SIGUSR1);
		usleep(4000);
	}
}
