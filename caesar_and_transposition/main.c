#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SHIFT 3

void caesar(char *text, int shift, int decrypt) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char aux = isupper(text[i]) ? 'A' : 'a';
            text[i] = aux + (text[i] - aux + (decrypt ? -shift : shift) + 26) % 26;
        }
    }
}


void transpose_cipher(char *text, int decrypt) {
    int len = strlen(text);
    if (len < 2) return;

    char *temp = (char *)malloc(len + 1);
    if (!temp) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    strcpy(temp, text);

    if (!decrypt) {
        for (int i = 0; i < len - 1; i++) {
            if (isalpha(temp[i]) && isalpha(temp[i + 1])) {
                char aux = temp[i];
                temp[i] = temp[i + 1];
                temp[i + 1] = aux;
                i++;
            }
        }
    } else {
        for (int i = 0; i < len - 1; i++) {
            if (isalpha(temp[i]) && isalpha(temp[i + 1])) {
                char aux = temp[i];
                temp[i] = temp[i + 1];
                temp[i + 1] = aux;
                i++;
            }
        }
    }

    strcpy(text, temp);
    free(temp);
}



void process_file(const char *input_file, const char *output_file, int decrypt) {
    FILE *fin = fopen(input_file, "r");
    if (!fin) {
        fprintf(stderr, "Input file: %s not found\n", input_file);
        exit(1);
    }

    FILE *fout = fopen(output_file, "w");
    if (!fout) {
        fprintf(stderr, "Output file: %s not found\n", output_file);
        fclose(fin);
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        caesar(buffer, SHIFT, decrypt);
        transpose_cipher(buffer, decrypt);
        fputs(buffer, fout);
        fputc('\n', fout);
    }

    fclose(fin);
    fclose(fout);
}

int main(int argc, char *argv[]) {
    if (argc != 5 || (strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0) || strcmp(argv[3], "-o") != 0) {
        fprintf(stderr, "Please insert an input like: -e|-d input_file -o output_file\n");
        return 1;
    }

    int decrypt = (strcmp(argv[1], "-d") == 0);
    process_file(argv[2], argv[4], decrypt);

    printf("Success! Output saved to %s\n", argv[4]);
    return 0;

}
