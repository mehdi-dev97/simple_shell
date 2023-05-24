#include "main.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t reader = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		reader = getline(buf, &len_p, stdin);
#else
		reader = _getline(info, buf, &len_p);
#endif
		if (reader > 0)
		{
			if ((*buf)[reader - 1] == '\n')
			{
				(*buf)[reader - 1] = '\0';
				reader--;
			}
			info->line_count_flag = 1;
			delete_comments(*buf);
			build_backup_list(info, *buf, info->backcount++);
			{
				*len = reader;
				info->cmd_buf = buf;
			}
		}
	}
	return (reader);
}

/**
 * prompt - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t prompt(info_t *info)
{
	static char *buffer;
	char **buffer_pointer = &(info->arg), *ptr;
	static size_t length, i, j;
	ssize_t reader = 0;

	print_char(BUFFER_FLUSH);
	reader = input_buf(info, &buffer, &length);
	if (reader == -1)
	{
		return (-1);
	}
	if (length)
	{
		j = i;
		ptr = buffer + i;
		check_chain(info, buffer, &j, i, length);
		while (j < length)
		{
			if (is_chain(info, buffer, &j))
			{
				break;
			}
			j++;
		}
		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buffer_pointer = ptr;
		return (string_length(ptr));
	}
	*buffer_pointer = buffer;
	return (reader);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t reader = 0;

	if (*i)
	{
		return (0);
	}
	reader = read(info->read_file_descriptor, buf, RD_BUFFER_SIZE);
	if (reader >= 0)
	{
		*i = reader;
	}
	return (reader);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[RD_BUFFER_SIZE];
	char *pointer = NULL, *new_pointer = NULL, *c;
	ssize_t reader = 0, size = 0;
	static size_t i, len;
	size_t k;

	pointer = *ptr;
	if (pointer && length)
	{
		size = *length;
	}
	if (i == len)
	{
		i = len = 0;
	}
	reader = read_buf(info, buffer, &len);
	if (reader == -1 || (reader == 0 && len == 0))
	{
		return (-1);
	}
	c = string_search(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_pointer = realloc_memory(pointer, size, size ? size + k : k + 1);
	if (!new_pointer)
	{
		return (pointer ? free(pointer), -1 : -1);
	}
	if (size)
	{
		string_concat_number(new_pointer, buffer + i, k - i);
	}
	else
	{
		string_copy_numbers(new_pointer, buffer + i, k - i + 1);
	}
	size += k - i;
	i = k;
	pointer = new_pointer;
	if (length)
	{
		*length = size;
	}
	*ptr = pointer;
	return (size);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_print("\n");
	_print("($) ");
	print_char(BUFFER_FLUSH);
}

