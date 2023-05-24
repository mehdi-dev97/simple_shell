#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define RD_BUFFER_SIZE 1024
#define WR_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define USE_GETLINE 0
#define USE_STRTOK 0

#define TO_LOWERCASE 1
#define TO_UNSIGNED 2

#define BACK_FILE ".simple_shell_back"
#define BACK_MAX 4096

extern char **environ;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct pseudo_arg_pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_number;
	int line_count_flag;
	char *file_name;
	list_t *envirment;
	list_t *backup;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int read_file_descriptor;
	int backcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} built_tb;

void find_cmd(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);
int find_builtin(info_t *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

/* String functions */
char *string_start_with(const char *, const char *);
int string_compare(char *, char *);
char *string_concat(char *, char *);
int string_length(char *);
char *string_copy(char *, char *);
char *string_duplicate(const char *str);
char *string_copy_numbers(char *, char *, int num);
char *string_search(char *, char);
char *string_concat_number(char *, char *, int);
char **string_to_word(char *, char *);
char **string_to_words(char *, char);

/* Print functions */
int print_char(char);
void _print(char *);
int print_file_descriptor(char *str, int fd);
int print_decimal(int, int);
void error_print(info_t *, char *);

/* Puts functions */
int error_put_char(char);
int put_file_descriptor(char c, int fd);
void error_puts(char *);

/* Memory functions */
void free_memory(char **);
char *fill_memory(char *, char, unsigned int);
void *realloc_memory(void *, unsigned int, unsigned int);
int byte_free(void **);

/* Convertion functions */
int is_separator(char, char *);
int _isalpha(int);
int interactive(info_t *);
int string_to_int(char *);

char *convert_number(long int, int, int);
int _erratoi(char *);
void delete_comments(char *);

int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

int _myalias(info_t *);
int _myhistory(info_t *);

void sigintHandler(int);
ssize_t prompt(info_t *);
int _getline(info_t *, char **, size_t *);

void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);

/* Env functions */
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _myenv(info_t *);
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);

/* Backup files functions */
char *get_backup(info_t *inf);
int read_backup(info_t *inf);
int build_backup_list(info_t *inf, char *buffer, int line_count);
int history_backup(info_t *inf);
int create_backup(info_t *inf);

list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);
void free_list(list_t **);

size_t list_len(const list_t *);
list_t *node_string_start_with(list_t *, char *, char);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);

void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);

#endif

