/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:45:23 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 13:25:22 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_env	*ft_env_new(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key ? strdup(key) : NULL;
	new->value = value ? strdup(value) : NULL;
	new->next = NULL;
	return (new);
}

t_env	*ft_env_dup(t_env *env)
{
	t_env	*new_list = NULL;
	t_env	*tail = NULL;
	t_env	*tmp;

	while (env)
	{
		tmp = ft_env_new(env->key, env->value);
		if (!tmp)
		{
			// gestion d'erreur → free la liste déjà copiée
			while (new_list)
			{
				t_env *to_free = new_list;
				new_list = new_list->next;
				free(to_free->key);
				free(to_free->value);
				free(to_free);
			}
			return (NULL);
		}
		if (!new_list)
			new_list = tmp;
		else
			tail->next = tmp;
		tail = tmp;
		env = env->next;
	}
	return (new_list);
}

void	print_cmd(t_cmd *cmd)
{
	int		j;
	int		k;
	t_redir	*redir_tmp;
	t_cmd	*cmd_tmp;

	k = 0;
	cmd_tmp = cmd;
	while (cmd_tmp)
	{
		j = 0;
		redir_tmp = cmd_tmp->redirect;
		while (cmd_tmp->args[j])
		{
			fprintf(stderr, "CMD ARGS [%d]: %s\n", j, cmd_tmp->args[j]);
			j++;
		}
		while (redir_tmp)
		{
			fprintf(stderr, "TYPE [%d]: %d\n", k, redir_tmp->type);
			fprintf(stderr, "FILE [%d]: %s\n", k, redir_tmp->file);
			k++;
			redir_tmp = redir_tmp->next;
		}
		cmd_tmp = cmd_tmp->next;
	}
}

void	print_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (!token)
		return ;
	while (tmp)
	{
		printf("VALUE AU RANG [%d]: %s\n", i, tmp->value);
		printf("TYPE AU RANG [%d]: %d\n", i, (int)tmp->type);
		printf("NEED EXPAND AU RANG [%d]: %d\n", i, tmp->need_exp);
		printf("QUOTES AU RANG [%d]: %d\n", i, tmp->state);
		i++;
		tmp = tmp->next;
	}
	printf("FIN DE PRINT TOKEN\n\n");
}

void	printr(char *message)
{
	printf("minishell: syntax error near unexpected token `%s'\n", message);
}
