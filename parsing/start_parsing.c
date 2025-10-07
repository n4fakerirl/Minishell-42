/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:13:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/07 11:33:28 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void util_trim(t_token *tmp, char *new_value, char c)
{
	int len;
	
	len = ft_strlen(tmp->value);
	if (len >= 2 && tmp->value[0] == c && tmp->value[len - 1] == c)
	{
		new_value = ft_substr(tmp->value, 1, len - 2);
		free(tmp->value);
		tmp->value = ft_strdup(new_value);
		free(new_value);
	}
}

void trim_litt(t_token *tmp, char *new_value, char c)
{
	int len;
	
	len = ft_strlen(tmp->value);
	if (len >= 2 && tmp->value[1] == c && tmp->value[len - 1] == c)
	{
		new_value = ft_substr(tmp->value + 1, 1, len - 2);
		free(tmp->value);
		tmp->value = ft_strdup(new_value);
		free(new_value);
	}
}

void	trim_words(t_token *tokens)
{
	t_token	*tmp;
	char	*new_value;

	tmp = tokens;
	while (tmp)
	{
		new_value = ft_strdup("");
		if (tmp->type == WORD && !ft_strncmp(tmp->value, "$\"", 2))
			trim_litt(tmp, new_value, '\"');
		if (tmp->type == WORD && !ft_strncmp(tmp->value, "$\'", 2))
			trim_litt(tmp, new_value, '\'');
		else if (tmp->type == WORD && tmp->state == DOUBLE_QUOTE)
			util_trim(tmp, new_value, '\"');
		else if (tmp->type == WORD && tmp->state == SINGLE_QUOTE)
			util_trim(tmp, new_value, '\'');
		tmp = tmp->next;
	}
	free(new_value);
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
	printf("MON TOKEN :\n");
	print_token(tokens);
	trim_words(tokens);
	del_quotes(tokens);
	cmd_list(tokens, &shell->cmd, shell->env, exit_status);
	printf("MA CMD :\n");
	print_cmd(shell->cmd);
	//free_token(tokens);
	return (shell);
}
