#include "main.h"

/**
 * get_backup - gets backup file
 * @inf: info_t struct parameter
 *
 * Return: buffer string containg backup name
 */

char *get_backup(info_t *inf)
{
	char *buffer, *directory;

	directory = _getenv(inf, "HOME=");
	if (!directory)
	{
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (string_length(BACK_FILE) + string_length(directory) + 2));
	if (!buffer)
	{
		return (NULL);
	}
	buffer[0] = 0;
	string_copy(buffer, directory);
	string_concat(buffer, "/");
	string_concat(buffer, BACK_FILE);
	return (buffer);
}

/**
 * create_backup - creates a backup file or appends to file
 * @inf: info_t struct parameter
 *
 * Return: 1 (Success) -1 on error
 */
int create_backup(info_t *inf)
{
	ssize_t file_descriptor;
	char *file_name = get_backup(inf);
	list_t *node = NULL;

	if (!file_name)
	{
		return (-1);
	}
	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
	{
		return (-1);
	}
	for (node = inf->backup; node; node = node->next)
	{
		print_file_descriptor(node->str, file_descriptor);
		put_file_descriptor('\n', file_descriptor);
	}
	put_file_descriptor(BUFFER_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_backup - reads backup file
 * @inf: info_t struct parameter
 *
 * Return: count (Success) 0 on failed
 */
int read_backup(info_t *inf)
{
	ssize_t file_descriptor, reader_len, file_size = 0;
	char *buffer = NULL, *file_name = get_backup(inf);
	int i, last = 0, line_count = 0;
	struct stat st;

	if (!file_name)
		return (0);

	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	reader_len = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (reader_len <= 0)
		return (free(buffer), 0);

	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_backup_list(inf, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_backup_list(inf, buffer + last, line_count++);

	free(buffer);
	inf->backcount = line_count;
	while (inf->backcount-- >= BACK_MAX)
		delete_node_at_index(&(inf->backup), 0);
	history_backup(inf);
	return (inf->backcount);
}

/**
 * build_backup_list - build backup linked list
 * @inf: info_t struct parameter
 * @buffer: buffer
 * @line_count: backup line count
 *
 * Return: Always 0
 */
int build_backup_list(info_t *inf, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (inf->backup)
		node = inf->backup;
	add_node_end(&node, buffer, line_count);

	if (!inf->backup)
		inf->backup = node;
	return (0);
}

/**
 * history_backup - save history linked list in changes
 * @inf: info_t struct parameter
 *
 * Return: the new backcount
 */
int history_backup(info_t *inf)
{
	list_t *node = inf->backup;
	int i = 0, count = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	count = inf->backcount = i;
	return (count);
}

