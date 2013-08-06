#include <stdio.h>
#include <string.h>

int
main (int argc, char *argv[])
{
    char *progname;
    FILE *fp;

    if (argc < 2) {
        printf("usage: makemain filename.c\n");
        return 1;
    }
    /* create program name, chop after first . */
    progname = strdup(argv[1]);
    if (progname == NULL) {
        perror("strdup");
        return 2;
    }
    char *dot = strchr(progname, '.');
    if (dot == NULL) {
        printf("usage: makemain filename.c, input => [%s]\n", argv[1]);
        return 1;
    }
    *dot = '\0';

    /* Create main file */
    fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror("fopen");
        return 3;
    }
    fprintf(fp, "#include <stdio.h>\n");
    fprintf(fp, "\n");
    fprintf(fp, "int\n");
    fprintf(fp, "main (int argc, char *argv[])\n");
    fprintf(fp, "{\n");
    fprintf(fp, "    printf(\"automatically created %s\\n\");\n", progname);
    fprintf(fp, "    return 0;\n");
    fprintf(fp, "}\n");
    fclose(fp);

    /* Create Makefile */
    fp = fopen("Makefile", "w");
    if (fp == NULL) {
        perror("fopen Makefile");
        return 4;
    }
    fprintf(fp, "CFLAGS = -g -Wall\n");
    fprintf(fp, "SRCS = %s\n", argv[1]);
    fprintf(fp, "CC = gcc\n");
    fprintf(fp, "LDFLAGS =\n");
    fprintf(fp, "LDLIBS = -lpthread -lc -lrt\n");
    fprintf(fp, "\n");
    fprintf(fp, "PROGS = %s\n", progname);
    fprintf(fp, "\n");
    fprintf(fp, "all:$(PROGS)\n");
    fprintf(fp, "\n");
    fprintf(fp, "%s: %s\n", progname, argv[1]);
    fprintf(fp, "\t$(CC) -g $< -o $@ $(CFLAGS) $(LDFLAGS)\n");
    fprintf(fp, "\n");
    fprintf(fp, "clean:\n");
    fprintf(fp, "\trm $(PROGS) *core*\n");
    return 0;
}
