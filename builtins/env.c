/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:34:26 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/13 20:09:08 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(char **split, t_env *env, bool egal)
{
	if (split[1])
	{
		ft_putstr_fd("minishell: env: ", 2);
		ft_putstr_fd(split[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	while (env)
	{
		if (!env->value && egal)
			printf("%s=\n", env->key);
		else if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
