/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:27:34 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 12:46:25 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_end_simple(char c)
{
	if (c == '|' || c == '\0')
		return (1);
	return (0);
}

static int	at_redir(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (*s == '>' || *s == '<')
		return (1);
	
	// Check for file descriptor redirection (digit followed by > or <)
	i = 0;
	if (ft_isdigit(s[i]))
	{
		while (s[i] && ft_isdigit(s[i]))
			i++;
		if (s[i] == '>' || s[i] == '<')
			return (1);
	}
	
	return (0);
}

static void	handle_args(t_cmd *cmd, char *cmd_name, t_cmd_params *params)
{
	int		arg_count;
	char	*arg;

	arg_count = 0;
	cmd->args = malloc(sizeof(char *) * 256);
	if (!cmd->args)
		return ;
	cmd->args[arg_count] = ft_strdup(cmd_name);
	if (!cmd->args[arg_count])
		return (free(cmd->args));
	arg_count++;
	while (*(params->shell_input->input)
		&& !is_end_simple(*(params->shell_input->input)))
	{
		skip_space(&(params->shell_input->input));
		if (!*(params->shell_input->input)
			|| is_end_simple(*(params->shell_input->input)))
			break ;
		if (at_redir(params->shell_input->input))
		{
			parse_one_redirection(cmd, params->shell_input);
			if (!params->shell_input->is_valid)
				break ;
			continue ;
		}
		arg = grab_word_with_env(&(params->shell_input->input),
				params->envp, params->shell);
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

static void	attach_pending_redirections(t_cmd *cmd, t_shell_input *shell_input)
{
	t_redirect	*cur;

	// Attach pending input redirections
	if (shell_input->pending_in_redir)
	{
		if (!cmd->in_redir)
			cmd->in_redir = shell_input->pending_in_redir;
		else
		{
			cur = cmd->in_redir;
			while (cur->next)
				cur = cur->next;
			cur->next = shell_input->pending_in_redir;
		}
		shell_input->pending_in_redir = NULL;
	}

	// Attach pending output redirections
	if (shell_input->pending_out_redir)
	{
		if (!cmd->out_redir)
			cmd->out_redir = shell_input->pending_out_redir;
		else
		{
			cur = cmd->out_redir;
			while (cur->next)
				cur = cur->next;
			cur->next = shell_input->pending_out_redir;
		}
		shell_input->pending_out_redir = NULL;
	}
}

void	handle_cmd(t_shell_input *shell_input, char **envp, t_shell *shell)
{
	t_cmd			*cmd;
	char			*cmd_name;
	t_cmd_params	params;

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
	
	// Attach any pending redirections to this command
	attach_pending_redirections(cmd, shell_input);
	
	params.shell_input = shell_input;
	params.envp = envp;
	params.shell = shell;
	handle_args(cmd, cmd_name, &params);
	append_to_linked_list(shell_input, cmd);
}

