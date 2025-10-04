/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:13:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 19:18:38 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	trim_words(t_token *tokens)
{
	t_token	*tmp;
	char	*new_value;
	int		len;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->state == DOUBLE_QUOTE)
		{
			len = ft_strlen(tmp->value);
			if (len >= 2 && tmp->value[0] == '"' && tmp->value[len - 1] == '"')
			{
				new_value = ft_substr(tmp->value, 1, len - 2);
				free(tmp->value);
				tmp->value = new_value;
			}
		}
		else if (tmp->type == WORD && tmp->state == SINGLE_QUOTE)
		{
			len = ft_strlen(tmp->value);
			if (len >= 2 && tmp->value[0] == '\'' && tmp->value[len
				- 1] == '\'')
			{
				new_value = ft_substr(tmp->value, 1, len - 2);
				free(tmp->value);
				tmp->value = new_value;
			}
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
	need_expand(tokens);
	trim_words(tokens);
	cmd_list(tokens, &shell->cmd, shell->env, exit_status);
	// print_token(tokens);
	// free_token(tokens);
	return (shell);
}
