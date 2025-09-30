/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:11:46 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/27 15:47:40 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*new_redir(void)
{
	t_redir	*redir;
	
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup("b");
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->type = REDIRDL;
	redir->next = NULL;
	return (redir);
}

t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup("a");
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->type = REDIRDL;
	//redir->next = NULL;
	redir->next = new_redir();
	return (redir);
}

void	change_redir(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	tmp = tmp->next;
	tmp->redirect = NULL;
	//tmp->redirect->next = NULL;
	//tmp = tmp->next;
	//tmp->redirect = NULL;
	//tmp = tmp->next;
	//tmp->redirect->type = REDIRL;
	//tmp->redirect->next->type = REDIRDR;
	//tmp->redirect->next->next = NULL;
	//tmp->next = NULL;
}

t_cmd	*create_node(char **split, int start, int end)
{
	t_cmd	*new_node;
	int		i;
	int		len;

	i = 0;
	len = end - start;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = malloc(sizeof(char *) * (len + 1));
	if (!new_node->args)
	{
		free_cmd(new_node);
		return (NULL);
	}
	while (start < end)
	{
		new_node->args[i] = ft_strdup(split[start]);
		i++;
		start++;
	}
	new_node->args[i] = 0;
	new_node->here_doc = 0;
	new_node->redirect = init_redir();
	//new_node->redirect = NULL;
	new_node->next = NULL;
	return (new_node);
}	

t_cmd	*init_cmd(char **split)
{
	t_cmd *head;
	t_cmd	*new_node;
	t_cmd	*tmp;
	int	len;
	int	start;
	int	size;
	int	end;
	
	end = 0;
	len = 0;
	start = 0;
	head = NULL;
	size = split_len(split);
	while (split[len])
	{
		if (split[len][0] == '\0')
			break ;
		else if (split[len][0] == '|' || len + 1 == size)
		{
			end = len; 
			if (len + 1 == size)
				end = size;
			new_node = create_node(split, start, end);
			if (!head)
				head = new_node;
			else
			{
				tmp = head;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_node;
			}
			start = len + 1;
		}
		len++;
	}
	return (head);
}