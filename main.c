/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/06 20:00:17 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, cmd, "unset") || !ft_strcmp(cmd, cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
} */

int exec_builtin(char **split, int *exit_status)
{
	if (!ft_strcmp(split[0], "echo"))
		return (ft_echo(split));
	else if (!ft_strcmp(split[0], "cd"))
		return (ft_cd(split));
	else if (!ft_strcmp(split[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(split[0], "export"))
		return (ft_export(split));
	else if (!ft_strcmp(split[0], "unset"))
		return (ft_unset(split));
	else if (!ft_strcmp(split[0], "env"))
		return (ft_env(split));
	else if (!ft_strcmp(split[0], "exit"))
		return (ft_exit(split, exit_status));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int		exit_status;
	char	**split;

	exit_status = 0;
	split = ft_split(av);
	if (!split || !split[0])
		return (1);
	env_conv(envp);
	exec_builtin(split, env, &exit_status);
}
