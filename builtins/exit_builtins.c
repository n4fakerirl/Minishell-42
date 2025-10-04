/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:44:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/13 16:33:39 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	chdir_exit(char *message, char *path)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	cwd_exit(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	getpwd_exit(char *message)
{
	ft_putstr_fd(message, 2);
}

void	exit_lit(char *message)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	exit_num(char *message)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": too many arguments\n", 2);
}
