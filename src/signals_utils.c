/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:12 by mde-souz          #+#    #+#             */
/*   Updated: 2024/07/20 18:03:35 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	send_str_with_signal(int pid, char *str)
{
	int	j;
	char	*byte;
	//extern int	count;
	
	j = 0;
	//ft_printf(1,"%s\n", str);
	while (str[j])
	{
		byte = ft_char_to_byte(str[j]);
		while (*byte)
		{
			//ft_printf(1,"%c", *byte);
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
			usleep(42);
			//ft_printf(1, "count = %d\n",++count);
		}
		//ft_printf(1," Acabou o byte do %c\n", str[j]);
		j++;
	}
	//ft_printf(1,"\n");
}

void	send_str_with_signal_sleep(int pid, char *str, int usec)
{
	int	j;
	char	*byte;
	//extern int	count;
	
	j = 0;
	//ft_printf(1,"%s\n", str);
	while (str[j])
	{
		byte = ft_char_to_byte(str[j]);
		while (*byte)
		{
			//ft_printf(1,"%c", *byte);
			if (*byte++ == '0')
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(usec);
		}
		//ft_printf(1," Acabou o byte do %c\n", str[j]);
		j++;
	}
	//ft_printf(1,"\n");
}

void	send_null_with_signal(int pid)
{
	int	j;
	
	j = 8;
	while (j--)
	{
		ft_printf(1,"0");
		kill(pid, SIGUSR1);
		usleep(2000);
	}
	ft_printf(1," Acabou o byte do null");
}
