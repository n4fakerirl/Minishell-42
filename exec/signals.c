/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:24:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 18:59:00 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile	sig_atomic_t	g_signal = 0;

void sigint_handler(int sig)
{
    (void)sig;
    g_signal = SIGINT;
   	write(1, "\n", 1);
    //rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}



