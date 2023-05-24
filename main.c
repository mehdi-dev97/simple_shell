#include "main.h"

/**
 * main - entry shell point
 * @ac: arguments count
 * @av: arguments values
 *
 * Return: 0 (Success) 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int file_descriptor = 2;

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == ENOENT)
			{
				error_puts(argv[0]);
				error_puts(": 0: Can't open ");
				error_puts(argv[1]);
				error_put_char('\n');
				error_put_char(BUFFER_FLUSH);
				exit(127);
			}
			return (1);
		}
		info->read_file_descriptor = file_descriptor;
	}
	populate_env_list(info);
	read_backup(info);
	hsh(info, argv);
	return (0);
}

