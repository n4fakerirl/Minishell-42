/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:13:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 02:05:52 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	simple_quote(t_inquote quote)
{
	if (!quote.in_single)
		quote.in_single = 1;
	else
		quote.in_single = 0;
	return (1);
}

int	double_quote(t_inquote quote)
{
	if (!quote.in_double)
		quote.in_double = 1;
	else
		quote.in_double = 0;
	return (1);
}

char	*strip_quotes(char *str, int len, int i, int j)
{
	char		*result;
	t_inquote	quote;

	result = malloc(len + 1);
	quote.in_double = 0;
	quote.in_single = 0;
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !quote.in_double)
		{
			i += simple_quote(quote);
			continue ;
		}
		if (str[i] == '"' && !quote.in_single)
		{
			i += double_quote(quote);
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

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
