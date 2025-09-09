/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:30:26 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/09 19:57:15 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Affiche le repertoire courant
int	ft_pwd(void)
{
	char	*cwd;

	if ((cwd = getcwd(NULL, 0)) != NULL)
		printf("%s\n", cwd);
	else
	{
		ft_putstr_fd("minishell: pwd: erreur de récupération du répertoire courant :", 2);
		ft_putstr_fd("getcwd: impossible d'accéder aux répertoires parents :", 2);
		ft_putstr_fd("Aucun fichier ou dossier de ce type\n", 2);
		return (1);
	}
	return (0);
}