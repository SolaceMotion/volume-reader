// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint8_t BYTE;

typedef struct
{
    DWORD chunk_id;
    DWORD chunk_size;
    DWORD format;
    DWORD subchunk1_id;
    DWORD subchunk1_size;

    WORD audio_format;
    WORD num_channels;
    DWORD sample_rate;
    DWORD byte_rate;
    WORD block_align;
    WORD bits_per_sample;

    DWORD subchunk2_id;
    DWORD subchunk2_size;
    DWORD data;
} WAVHEADER;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    BYTE *buffer = malloc(sizeof(BYTE) * HEADER_SIZE);
    // TODO: Copy header from input file to output file
    fread(buffer, sizeof(BYTE) * HEADER_SIZE, 1, input);
    fwrite(buffer, sizeof(BYTE) * HEADER_SIZE, 1, output);

    /* fseek(input, 0, SEEK_END);
    long filelen = ftell(input);
    // TODO: Read samples from input file and write updated data to output file
    printf("%ld", filelen);
    rewind(input); */

    for (int i = 0; i < 2000; i++)
    {
        WORD sample;
        fread(&sample, sizeof(WORD), 1, input);
        printf("%i", sample);
    }
    // Close files
    fclose(input);
    fclose(output);
}
