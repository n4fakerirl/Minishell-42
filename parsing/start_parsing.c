/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:13:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 02:51:56 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_dollar(t_token *tokens)
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
			free(tmp->value);
			tmp->value = ft_strdup(sub);
			free(sub);
		}
		tmp = tmp->next;
	}
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
	handle_dollar(tokens);
	expand_tokens(tokens, shell->env, exit_status);
	// printf("MON TOKEN :\n");
	// print_token(tokens);
	trim_word(tokens);
	cmd_list(tokens, &shell->cmd, 0);
	// printf("MA CMD :\n");
	// print_cmd(shell->cmd);
	// free_token(tokens);
	return (shell);
}
