#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char *str = "Temporary string to be written to file!";
const char *str2 = "\n";

int main(void) {
    const char* filename = "out.txt";

    FILE* output_file = fopen(filename, "w+");
    if (!output_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(str, 1, strlen(str), output_file);
    fwrite(str2, 1, strlen(str2), output_file);
    fwrite(str, 1, strlen(str), output_file);


    fclose(output_file);
    exit(EXIT_SUCCESS);
}