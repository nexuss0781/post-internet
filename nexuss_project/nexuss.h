#ifndef NEXUSS_H
#define NEXUSS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// .nexuss Mathematical Constants
#define NEXUS_BLOCK_SIZE 8      // Size of data block to map (in bytes)
#define NEXUS_KEY_MAX_SIZE 1024 // Max size of the Nexus Key in KB (simulated)

typedef struct {
    uint64_t position;
    uint32_t pattern_id;
} NexusPosition;

typedef struct {
    NexusPosition *positions;
    size_t count;
    uint64_t original_size;
} NexusKey;

// Core Functions
uint64_t universal_generator(uint64_t pos);
int encode_file_to_nexus(const char *input_path, const char *output_key_path);
int decode_file_from_nexus(const char *key_path, const char *output_path);
NexusKey* encode_to_nexus(const uint8_t *data, size_t size);
uint8_t* decode_from_nexus(const NexusKey *key, size_t *out_size);
void free_nexus_key(NexusKey *key);

#endif // NEXUSS_H
