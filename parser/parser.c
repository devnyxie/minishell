/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:59:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/05 19:58:23 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../minishell.h" // for t_shell and env access

// TODO: err msg, mem handle
t_shell_input *init_shell_input(char *input)
{
	t_shell_input *shell_input;

	shell_input = malloc(sizeof(t_shell_input));
	if (!shell_input)
	{
		return (NULL);
	}
	shell_input->first_cmd = NULL;
	shell_input->last_cmd = NULL;
	shell_input->is_valid = 1;
	shell_input->cmds_count = 0;
	shell_input->input = input;
	return (shell_input);
}

t_redirect_type redirect_type(t_shell_input *shell_input, t_cmd *cmd)
{
	t_redirect_type type;

	cmd = shell_input->last_cmd;
	if (!cmd)
	{
		// custom_error("syntax error: redirection with no command");
		shell_input->input++;
		return 0;
	}
	// Determine redirection type
	if (*(shell_input->input) == '>' && *(shell_input->input + 1) == '>')
	{
		type = REDIR_APPEND;
		shell_input->input += 2;
	}
	else if (*(shell_input->input) == '<' && *(shell_input->input + 1) == '<')
	{
		type = HEREDOC;
		shell_input->input += 2;
	}
	else if (*(shell_input->input) == '>')
	{
		type = REDIR_OUT;
		shell_input->input += 1;
	}
	else if (*(shell_input->input) == '<')
	{
		type = REDIR_IN;
		shell_input->input += 1;
	}
	else
		return 0;
	return (type);
}

// Helper: Get env value by key
char *get_env_value(char **envp, const char *key)
{
	int i = 0;
	size_t key_len = strlen(key);
	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return envp[i] + key_len + 1;
		i++;
	}
	return "";
}

void handle_expand_variables(char **envp, t_shell_input *shell_input)
{
	char *input = shell_input->input;
	char *new_input = ft_calloc(1, ft_strlen(input) + 1);
	int i = 0;

	while (input[i])
	{
		if (input[i] == '$' && (isalpha(input[i + 1]) || input[i + 1] == '_'))
		{
			i++; // skip '$'
			int var_start = i;

			while (isalnum(input[i]) || input[i] == '_')
				i++;

			char *var_name = ft_strndup(&input[var_start], i - var_start);
			char *value = get_env_value(envp, var_name);

			new_input = ft_realloc(new_input, ft_strlen(new_input) + ft_strlen(value) + 1);
			ft_strlcat(new_input, value, ft_strlen(new_input) + ft_strlen(value) + 1);
			free(var_name);
		}
		else
		{
			size_t len = ft_strlen(new_input);
			new_input = ft_realloc(new_input, len + 2);
			new_input[len] = input[i];
			new_input[len + 1] = '\0';
			i++;
		}
	}

	free(shell_input->input);
	shell_input->input = new_input;
}

static void handle_redirect(t_shell_input *parsed_input)
{
	t_cmd *cmd;
	t_redirect *redir;
	t_redirect_type type;
	char *file;

	cmd = parsed_input->last_cmd;
	type = redirect_type(parsed_input, cmd);
	skip_space(&parsed_input->input);
	file = grab_word(&parsed_input->input);
	printf("file: %s\n", file);
	if (!file)
	{
		static int i = 0;
		i++;
		printf("Entering function: %d time.\n", i);
		report_error(NULL, "syntax error near unexpected token `newline'", 0);
		return;
	}
	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return;
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	if (type == REDIR_IN || type == HEREDOC)
	{
		redir->next = cmd->in_redir;
		cmd->in_redir = redir;
	}
	else
	{
		redir->next = cmd->out_redir;
		cmd->out_redir = redir;
	}
}

/*
Is called for each byte, but the inner functions may move
the pointer of the input string for faster execution.
*/
void handle_input(t_shell *shell)
{
	char **input = &shell->parsed_input->input;
	// here shell->parsed_input->input should be equal to input, since in the next functions the pointer of parsed_input is updated

	handle_expand_variables(shell->envp, shell->parsed_input);
	if (**input == '>' || **input == '<')
		handle_redirect(shell->parsed_input);
	else if (**input == '|')
	{
		if (shell->parsed_input->first_cmd == NULL)
			report_error(NULL, "syntax error near unexpected token `|'", 0);
		if (**input)
			input++;
		handle_cmd(shell->parsed_input);
	}
	else if (is_space(**input) && **input)
	{

		(*input)++;
	}
	else
		handle_cmd(shell->parsed_input);
}

/*
The loop will continue as long as the input pointer
is valid. Inner functions move the ptr of the input.
*/
void parser(t_shell *shell, char *input)
{
	shell->parsed_input = init_shell_input(input);
	while (*(shell->parsed_input->input))
		handle_input(shell);
}