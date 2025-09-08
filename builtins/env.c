/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:56:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/08 11:12:24 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Affiche les variables d'environnement

void	init_env(t_env *env)
{
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
}

t_env	env_conv(char **envp)
{
	int		i;
	t_env	env;

	i = 0;
	init_env(&env);
	if (!envp | !*envp)
		return (NULL);
	while (envp[i])
	{
		
	}
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s", env->key, env->value);
		env = env->next;
	}
	return (0);
}
