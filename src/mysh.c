# define _GNU_SOURCE
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_LINE 1024
# define MAX_ARGS 128

static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n && s[n-1] == '\n') s[n-1] = '\0';
}

static void build_prompt(char *out, size_t cap) {
    char cwd[PATH_MAX]; getcwd(cwd, sizeof(cwd));
    char host[256]; gethostname(host, sizeof(host));
    const char *user = getenv("USER"); if (!user) user = "user";
    snprintf(out, cap, "%s@%s:%s$mysh> ", user, host, cwd);
}

static int parse(char *line, char *argv[]) {
    int argc = 0;
    char *tok = strtok(line, " \t");
    while (tok && argc < MAX_ARGS-1) {
        argv[argc++] = tok;
        tok = strtok(NULL, " \t");
    }
    argv[argc] = NULL;
    return argc;
}

static int bi_pwd(void) {
    char cwd[PATH_MAX];
    if (!getcwd(cwd, sizeof(cwd))) { perror("pwd"); return 1; }
    puts(cwd);
    return 0;
}

static int bi_cd(char *path) {
    if (!path) path = getenv("HOME");
    if (!path) { fprintf(stderr, "No such directory\n"); return 1; }
    if (chdir(path) == -1) {
        if (errno == ENOENT) fprintf(stderr, "No such directory\n");
        else fprintf(stderr, "Change directory failed\n");
        return 1;
    }
    return 0;
}

static bool is_builtin(const char *cmd) {
    return cmd && (!strcmp(cmd,"cd") || !strcmp(cmd,"pwd") || !strcmp(cmd,"exit"));
}

static int run_builtin(char *argv[]) {
    if (!strcmp(argv[0], "pwd")) return bi_pwd();
    if (!strcmp(argv[0], "cd"))  return bi_cd(argv[1]);
    if (!strcmp(argv[0], "exit")) exit(0);
    return 1;
}

static int run_external(char *argv[]) {
    pid_t pid = fork();
    if (pid < 0) { fprintf(stderr, "Failed to create process\n"); return 1; }
    if (pid == 0) {
        execvp(argv[0], argv);
        fprintf(stderr, "Failed to execute command\n");
        _exit(127);
    }
    int status=0; waitpid(pid, &status, 0);
    return WIFEXITED(status)? WEXITSTATUS(status) : 1;
}

int main(void) {
    char line[MAX_LINE];
    char prompt[PATH_MAX + 64];

    while (1) {
        build_prompt(prompt, sizeof(prompt));

	// build readline instead of fgets
	char *lineptr = readline(prompt);
	if (!lineptr) { puts(""); break; }	// Ctrl D
	if (*lineptr) add_history(lineptr);	// save non-empty commands to history

	// copy into fixed buffer for parsing, then free
	strncpy(line, lineptr, sizeof(line));
	line[sizeof(line)-1] = '\0';
	free(lineptr);

	trim_newline(line);
	if (!*line) continue;  // harmless even if no '\n'



        char *argv[MAX_ARGS];
        char tmp[MAX_LINE]; strncpy(tmp, line, sizeof(tmp)); tmp[sizeof(tmp)-1]='\0';
        int argc = parse(tmp, argv);
        if (argc == 0) continue;

        int rc = is_builtin(argv[0]) ? run_builtin(argv) : run_external(argv);
        (void)rc; // placeholder to avoid unused warning for now
    }
    return 0;
}
