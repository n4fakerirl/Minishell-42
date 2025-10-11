/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:13:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 21:18:33 by lenakach         ###   ########.fr       */
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

void	start_parsing(char *str, int exit_status, t_shell *shell)
{
	t_token	*tokens;

	tokens = tokenize(str);
	if (!tokens)
		return (free_shell(shell));
	new_type(tokens);
	if (!parse_args(tokens))
		return (free_shell(shell), free_token(tokens));
	quoting(tokens);
	need_expand(tokens);
	if (!handle_dollar(tokens))
		return (free_shell(shell), free_token(tokens));
	if (!expand_tokens(tokens, shell->env, exit_status))
		return (free_shell(shell), free_token(tokens));
	if (!trim_word(tokens))
		return (free_shell(shell), free_token(tokens));
	if (!cmd_list(tokens, &shell->cmd, 0))
		return (free_shell(shell), free_token(tokens));
	shell->head_cmd = shell->cmd;
	free_token(tokens);
}
