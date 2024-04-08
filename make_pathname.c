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
        free(path); // Important: Free the allocated memory!
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

    size_t dirlen = strlen(dir);
    size_t filelen = strlen(fname);
    size_t extlen = strlen(ext);

    // Calculate needed memory size (+3 for "/", "." and the null terminator)
    size_t size = dirlen + 1 + filelen + 1 + extlen + 1; // Updated calculation
    char *result = (char *)malloc(size);
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    // Use the provided block for secure and efficient copying
    if (dirlen > 0) {
        memcpy(result, dir, dirlen);
    }
    result[dirlen] = '/';

    if (filelen > 0) {
        memcpy(result + dirlen + 1, fname, filelen);
    }
    result[dirlen + 1 + filelen] = '.';

    if (extlen > 0) {
        memcpy(result + dirlen + 1 + filelen + 1, ext, extlen);
    }

    result[dirlen + 1 + filelen + 1 + extlen] = '\0'; // Ensure the string is null-terminated

    return result;
}
