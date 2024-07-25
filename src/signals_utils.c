/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:12 by mde-souz          #+#    #+#             */
/*   Updated: 2024/07/22 18:16:48 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	send_str_with_signal(int pid, char *str)
{
	int	j;
	char	*byte;
	
	j = 0;
	while (str[j])
	{
		byte = ft_char_to_byte(str[j]);
		while (*byte)
		{
			if (*byte++ == '0')
			{
				while (kill(pid, SIGUSR1) == -1)
					;
			}
			else
			{
				while (kill(pid, SIGUSR2) == -1)
					;
			}		
			pause();
			usleep(125);
		}
		j++;
	}
}

void	send_str_with_signal_sleep(int pid, char *str, int usec)
{
	int	j;
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
