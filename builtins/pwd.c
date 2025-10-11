/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:30:26 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 19:24:41 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory : ",
			2);
		ft_putstr_fd("getcwd: cannot access parent directories :", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
