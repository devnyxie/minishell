/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:27:34 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 16:40:30 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_args(t_cmd *cmd, t_shell_input *shell_input, char *cmd_name,
		char **envp, t_shell *shell)
{
	int		arg_count;
	char	*arg;

	arg_count = 0;
	cmd->args = malloc(sizeof(char *) * 256);
	if (!cmd->args)
		return ;
	cmd->args[arg_count] = ft_strdup(cmd_name);
	if (!cmd->args[arg_count])
	{
		free(cmd->args);
		return ;
	}
	arg_count++;
	while (*(shell_input->input) && *(shell_input->input) != '>'
		&& *(shell_input->input) != '<' && *(shell_input->input) != '|')
	{
		arg = grab_word_with_env(&(shell_input->input), envp, shell);
		if (!arg)
			break ;
		cmd->args[arg_count++] = arg;
	}
	cmd->args[arg_count] = NULL;
}

void	append_to_linked_list(t_shell_input *shell_input, t_cmd *cmd)
{
	t_cmd	*last_cmd;

	if (!shell_input->first_cmd)
	{
		shell_input->first_cmd = cmd;
		shell_input->last_cmd = cmd;
		return ;
	}
	last_cmd = shell_input->first_cmd;
	while (last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	cmd->prev = last_cmd;
	last_cmd->next = cmd;
	shell_input->last_cmd = cmd;
	shell_input->cmds_count++;
}

static int	is_variable_assignment(char *cmd_name)
{
	int	i;

	if (!cmd_name || !*cmd_name)
		return (0);
	if (!ft_isalpha(cmd_name[0]) && cmd_name[0] != '_')
		return (0);
	i = 1;
	while (cmd_name[i] && cmd_name[i] != '=')
	{
		if (!ft_isalnum(cmd_name[i]) && cmd_name[i] != '_')
			return (0);
		i++;
	}
	return (cmd_name[i] == '=');
}

static void	handle_variable_assignment(char *assignment, t_shell *shell)
{
	char	*equals;
	char	*var_name;
	char	*var_value;

	equals = ft_strchr(assignment, '=');
	if (!equals)
		return ;
	*equals = '\0';
	var_name = assignment;
	var_value = equals + 1;
	if (is_valid_identifier(var_name))
		update_env_var(shell, var_name, var_value);
	*equals = '=';
}

void	handle_cmd(t_shell_input *shell_input, char **envp, t_shell *shell)
{
	t_cmd	*cmd;
	char	*cmd_name;

	cmd_name = grab_word_with_env(&(shell_input->input), envp, shell);
	if (!cmd_name)
		return ;
	shell_input->incomplete_pipe = 0;
	if (is_variable_assignment(cmd_name))
	{
		handle_variable_assignment(cmd_name, shell);
		free(cmd_name);
		return ;
	}
	cmd = init_cmd(cmd_name);
	handle_args(cmd, shell_input, cmd_name, envp, shell);
	append_to_linked_list(shell_input, cmd);
}
