#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void runFile(const char* path);
void runPrompt();

int main(int argc, char* argv[]) {
    if (argc > 2) {
        printf("Usage: copl [script]\n");
        return 64;
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
    return 0;
}

static void repl()
{
    char line[1024];

    for (;;)
    {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break; 
        }

        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
            break;
        }

        printf("You entered: %s\n", line); // Placeholder for processing input
    }
}
// Dummy implementations for now
void runFile(const char* path) {
    if (path == NULL) {
        fprintf(stderr, "Error: No file path provided.\n");
        return;
    }
    if (strlen(path) == 0) {
        fprintf(stderr, "Error: Empty file path provided.\n");
        return;
    }

    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", path);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    if (fileSize < 0) {
        fprintf(stderr, "Error: Could not determine file size.\n");
        fclose(file);
        return;
    }

    char *buffer = (char*)malloc(fileSize + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Not enough memory to read file.\n");
        fclose(file);
        return;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error: Could not read file.\n");
        free(buffer);
        fclose(file);
        return;
    }
    buffer[fileSize] = '\0'; // Null-terminate
    fclose(file);

    printf("Running file: %s\n", path);
    printf("File contents:\n%s\n", buffer); // Placeholder for run(buffer)

    free(buffer);
}

void runPrompt() {
    // REPL logic will go here (read–eval–print loop)

    char line[1024];

    for(;;)
    {
        printf("> ");

        if(!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break; 

            // interpret(line)


        }        
    }    
}

static char * readFile(const char *path) {
    if (path == NULL) {
        fprintf(stderr, "Error: No file path provided.\n");
        return NULL;
    }
    if (strlen(path) == 0) {
        fprintf(stderr, "Error: Empty file path provided.\n");
        return NULL;
    }

    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    if (fileSize < 0) {
        fprintf(stderr, "Error: Could not determine file size.\n");
        fclose(file);
        return NULL;
    }

    char *buffer = (char*)malloc(fileSize + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Not enough memory to read file.\n");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error: Could not read file.\n");
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[fileSize] = '\0'; // Null-terminate
    fclose(file);

    return buffer;
}

static void runFile(int argc, char *argv[]) {
    // initVM();

    if(argc == 1){
        repl();
    }
    else if(argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: copl [script]\n");
        exit(64);
    }

    // freeVM();
}