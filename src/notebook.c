#include "notebook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

Cell notebook[MAX_CELLS];
int cell_count = 0;

void run_cell(int cell_index) {
    mkdir(MEMORY_DIRECTORY, 0755);

    FILE *file = fopen(TEMP_FILENAME, "w");
    if (!file) return;

    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "int main() {\n");
    for (int current_cell = 0; current_cell <= cell_index; current_cell++) {
        fprintf(file, "%s\n", notebook[current_cell].code);
    }
    fprintf(file, "return 0; }\n");
    fclose(file);

    char command[256];
    snprintf(command, sizeof(command),
             "gcc %s -o %s && ./%s > %smemory_output.txt 2>&1",
             TEMP_FILENAME, OUTPUT_FILENAME, OUTPUT_FILENAME, MEMORY_DIRECTORY);
    int result = system(command);

    char output_file_path[256];
    snprintf(output_file_path, sizeof(output_file_path), "%smemory_output.txt", MEMORY_DIRECTORY);
    FILE *out = fopen(output_file_path, "r");
    if (out) {
        notebook[cell_index].output[0] = '\0';
        char line[MAX_CODE_LENGTH];
        while (fgets(line, sizeof(line), out)) {
            strncat(notebook[cell_index].output, line, MAX_CODE_LENGTH - strlen(notebook[cell_index].output) - 1);
        }
        fclose(out);
    }
    if (result != 0) {
        strncat(notebook[cell_index].output, "Compilation or execution error.\n", MAX_CODE_LENGTH - strlen(notebook[cell_index].output) - 1);
    }

    printf("\033[2J\033[H");
    printf("\033[0;36m");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║              C Notebook Pure Terminal Mode            ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Commands: :save  :load  :exit                         ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("Current cells: %d\n", cell_count);

    for (int show_cell = 0; show_cell <= cell_index; show_cell++) {
        printf("--- Cell %d ---\n", show_cell + 1);
        printf("%s\n", notebook[show_cell].code);
        printf("Output:\n%s\n", notebook[show_cell].output);
    }
}
