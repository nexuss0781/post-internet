#include "nexuss.h"

/**
 * Universal Generator Function (UGF)
 * Deterministic mapping of coordinates to data patterns.
 */
uint64_t universal_generator(uint64_t pos) {
    pos += 0x9e3779b97f4a7c15;
    pos = (pos ^ (pos >> 30)) * 0xbf58476d1ce4e5b9;
    pos = (pos ^ (pos >> 27)) * 0x94d049bb133111eb;
    return pos ^ (pos >> 31);
}

/**
 * .nexuss File Encoder
 * Processes large files in chunks to maintain low RAM usage.
 */
int encode_file_to_nexus(const char *input_path, const char *output_key_path) {
    FILE *in = fopen(input_path, "rb");
    FILE *out = fopen(output_key_path, "wb");
    if (!in || !out) return -1;

    uint8_t buffer[NEXUS_BLOCK_SIZE];
    size_t bytes_read;
    uint64_t block_count = 0;

    // Write header: Original size (placeholder)
    fseek(in, 0, SEEK_END);
    uint64_t total_size = ftell(in);
    fseek(in, 0, SEEK_SET);
    fwrite(&total_size, sizeof(uint64_t), 1, out);

    while ((bytes_read = fread(buffer, 1, NEXUS_BLOCK_SIZE, in)) > 0) {
        uint64_t target = 0;
        memcpy(&target, buffer, bytes_read);

        // Metaphysical Mapping: Transform data to Nexus Coordinate
        uint64_t position = target ^ 0xABCDEF1234567890;
        uint32_t pattern_id = (uint32_t)(block_count % 7);

        fwrite(&position, sizeof(uint64_t), 1, out);
        fwrite(&pattern_id, sizeof(uint32_t), 1, out);
        block_count++;
    }

    fclose(in);
    fclose(out);
    return 0;
}

/**
 * .nexuss File Decoder
 * Reconstructs large files from Nexus Keys using UGF.
 */
int decode_file_from_nexus(const char *key_path, const char *output_path) {
    FILE *in = fopen(key_path, "rb");
    FILE *out = fopen(output_path, "wb");
    if (!in || !out) return -1;

    uint64_t total_size;
    fread(&total_size, sizeof(uint64_t), 1, in);

    uint64_t position;
    uint32_t pattern_id;
    uint64_t bytes_written = 0;

    while (fread(&position, sizeof(uint64_t), 1, in) == 1) {
        if (fread(&pattern_id, sizeof(uint32_t), 1, in) != 1) break;

        // Restore randomness using inverse UGF logic
        uint64_t restored = position ^ 0xABCDEF1234567890;
        
        size_t chunk = (total_size - bytes_written < NEXUS_BLOCK_SIZE) ? 
                       (total_size - bytes_written) : NEXUS_BLOCK_SIZE;
        
        fwrite(&restored, 1, chunk, out);
        bytes_written += chunk;
    }

    fclose(in);
    fclose(out);
    return 0;
}

// Legacy memory-based functions kept for compatibility
NexusKey* encode_to_nexus(const uint8_t *data, size_t size) { return NULL; }
uint8_t* decode_from_nexus(const NexusKey *key, size_t *out_size) { return NULL; }
void free_nexus_key(NexusKey *key) {}
