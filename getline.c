#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("error");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file){
        perror("error opening file");
        return 1;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *lines[2] = {NULL, NULL};
    int count = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        if (count == 2) {
            free(lines[0]);
            lines[0] = lines[1];
        }
        lines[count % 2] = strdup(line);
        count++;
    }

    for (int i = 0; i < 2 && i < count; i++) {
        printf("%s", lines[(count + i - 2) % 2]);
        free(lines[(count + i -2) % 2]);
    }
    free(line);
    fclose(file);
    return 0;
}