/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:13:25 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/07 23:04:55 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *strip_quotes(char *str, int i, int j, int in_single)
{
    char    *result;
	int 	in_double;
 
    result = malloc(ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    in_double = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !in_double)
        {
            in_single = !in_single;
            i++;
            continue;
        }
        if (str[i] == '"' && !in_single)
        {
            in_double = !in_double;
            i++;
            continue;
        }
        result[j++] = str[i++];
    }
    result[j] = '\0';
    return (result);
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
    printf("MON TOKEN :\n");
	print_token(tokens);
	need_expand(tokens);
	expand_tokens(tokens, shell->env, exit_status);
	printf("MON TOKEN :\n");
	print_token(tokens);
	trim_word(tokens);
	cmd_list(tokens, &shell->cmd);
	// printf("MA CMD :\n");
	// print_cmd(shell->cmd);
	//free_token(tokens);
	return (shell);
}
