#include "minishell.h"
#include "structs.h"
#include <readline/readline.h>
#include <unistd.h>

static size_t	var_span(const char *p)
{
	size_t i;

	if (*p == '?')
		return (1);
	if (!(ft_isalpha((unsigned char)*p) || *p == '_'))
		return (0);
	i = 1;
	while (ft_isalnum((unsigned char)p[i]) || p[i] == '_')
		i++;
	return (i);
}

static int	write_var(int fd, const char *s, size_t n, t_shell *sh)
{
	char	*key;
	char	*val;

	key = ft_strndup(s, n);
	if (!key)
		return (-1);
	if (n == 1 && *s == '?')
		val = ft_itoa(sh->exit_code);
	else
		val = (char *)get_env_value(sh->envp, key);
	if (val && write(fd, val, ft_strlen(val)) < 0)
		val = NULL;
	if (n == 1 && *s == '?')
		free(val);
	free(key);
	return (val || n == 1) ? 0 : 0;
}

static int	write_expanded_line(int fd, const char *line, t_redirect *r, t_shell *sh)
{
	size_t i;
	size_t chunk;

	if (!r->expand)
		return (write(fd, line, ft_strlen(line)) < 0 ? -1 : 0);
	i = 0;
	chunk = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > chunk && write(fd, line + chunk, i - chunk) < 0)
				return (-1);
			i++;
			if (!line[i])
				return (write(fd, "$", 1) < 0 ? -1 : 0);
			{
				size_t vlen = var_span(line + i);
				if (!vlen && write(fd, "$", 1) < 0)
					return (-1);
				if (vlen && write_var(fd, line + i, vlen, sh) < 0)
					return (-1);
				i += vlen ? vlen : 0;
				chunk = i;
				continue ;
			}
		}
		i++;
	}
	if (i > chunk && write(fd, line + chunk, i - chunk) < 0)
		return (-1);
	else
		return (0);
}

int	run_single_heredoc(t_redirect *r, t_shell *sh)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)  // EOF (Ctrl+D)
			break ;
		if (ft_strcmp(line, r->file) == 0)
		{
			free(line);
			break ;
		}
		if (write_expanded_line(fd[1], line, r, sh) < 0
			|| write(fd[1], "\n", 1) < 0)
		{
			free(line);
			close(fd[0]);
			close(fd[1]);
			return (-1);
		}
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

int	prepare_heredocs(t_cmd *cmds, t_shell *sh)
{
	t_cmd		*c;
	t_redirect	*r;
	int			fd;

	c = cmds;
	while (c)
	{
		r = c->in_redir;
		while (r)
		{
			if (r->type == HEREDOC)
			{
				fd = run_single_heredoc(r, sh);
				if (fd < 0)
					return (-1);
				if (c->in_fd != -1)
					close(c->in_fd);
				c->in_fd = fd;
			}
			r = r->next;
		}
		c = c->next;
	}
	return (0);
}

