/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_talk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:13:15 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/15 18:34:48 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H
# include "../lib/libft/include/libft.h"
# include <signal.h>

void	send_str_with_signal(int pid, char *byte);
void	send_null_with_signal(int pid);
void	send_str_with_signal_sleep(int pid, char *byte, int usec);
#endif