#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype
char* make_pathname(const char *dir, const char *fname, const char *ext);

int main() {
    // Example usage
    char *path = make_pathname("usr/local/bin", "example", "txt");
    if (path != NULL) {
        printf("Pathname: %s\n", path);
        free(path); // Don't forget to free the allocated memory!
    } else {
        printf("Failed to allocate memory for the pathname.\n");
    }
    return 0;
}

// Function definition
char* make_pathname(const char *dir, const char *fname, const char *ext) {
    // Check input validity (simplified check)
    if (dir == NULL || fname == NULL || ext == NULL) {
        return NULL;
    }

    for (int i = 0; fname[i] != '\0'; ++i) {
        if (fname[i] == '/' || fname[i] == '.') return NULL;
    }
    for (int i = 0; ext[i] != '\0'; ++i) {
        if (ext[i] == '/' || ext[i] == '.') return NULL;
    }

    // Calculate needed memory size (+3 for "/", "." and the null terminator)
    size_t size = strlen(dir) + strlen(fname) + strlen(ext) + 3;
    char *result = (char *)malloc(size);
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    // Construct the path
    strcpy(result, dir);
    strcat(result, "/");
    strcat(result, fname);
    strcat(result, ".");
    strcat(result, ext);

    return result;
}
