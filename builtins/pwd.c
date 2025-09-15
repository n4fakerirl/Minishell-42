/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:30:26 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/15 14:08:40 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
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
