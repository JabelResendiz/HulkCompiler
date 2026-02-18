
#include "logger.h"
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>

static FILE *log_file = NULL;

static const char *level_str[] = {
    "DEBUG", "INFO", "WARN", "ERROR"
};

void logger_init(const char *filename)
{
    log_file = fopen(filename, "w");

    if (!log_file) {
        perror("logger_init: cannot open log file");
        exit(1); // fallo crítico
    }
}

void logger_close()
{
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

void log_message(LogLevel level, const char *fmt, ...)
{
    if (!log_file) return; // logger not initialized

    /* timestamp */
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timebuf[32];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", t);

    /* prefix */
    fprintf(log_file, "[%s] [%s] ", timebuf, level_str[level]);

    /* formatted message */
    va_list args;
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);

    fprintf(log_file, "\n");
    fflush(log_file);
}
