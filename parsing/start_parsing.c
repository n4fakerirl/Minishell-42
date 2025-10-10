/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:13:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/10 17:14:24 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_dollar(t_token *tokens)
{
	char	*sub;
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->value[0] == '$' && (tmp->value[1] == '\"'
				|| tmp->value[1] == '\''))
		{
			sub = ft_strdup(tmp->value + 1);
			if (!sub)
				return (0);
			free(tmp->value);
			tmp->value = sub;
		}
		tmp = tmp->next;
	}
	return (1);
}

t_shell	*start_parsing(char *str, char **envp, int exit_status)
{
	t_shell	*shell;
	t_token	*tokens;

	shell = init_shell(envp, exit_status);
	if (!shell)
		return (NULL);
	tokens = tokenize(str);
	if (!tokens)
		return (free_shell(shell), NULL);
	new_type(tokens);
	if (!parse_args(tokens))
		return (free_shell(shell), free_token(tokens), NULL);
	quoting(tokens);
	need_expand(tokens);
	if (!handle_dollar(tokens))
		return (free_shell(shell), free_token(tokens), NULL);
	if (expand_tokens(tokens, shell->env, exit_status))
		return (free_shell(shell), free_token(tokens), NULL);
	if (!trim_word(tokens))
		return (free_shell(shell), free_token(tokens), NULL);
	if (!cmd_list(tokens, &shell->cmd, 0))
		return (free_shell(shell), free_token(tokens), NULL);
	free_token(tokens);
	return (shell);
}
