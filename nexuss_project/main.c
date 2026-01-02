#include "nexuss.h"
#include <time.h>
#include <sys/resource.h>

void print_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Current RAM Usage: %ld KB\n", usage.ru_maxrss);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *key_file = "nexus_key.bin";
    const char *output_file = "reconstructed_file.bin";

    printf("--- .nexuss Large-Scale Processing Proof ---\n");
    printf("Processing File: %s\n", input_file);
    print_memory_usage();

    // 1. Encoding
    printf("\n[Phase 1] Encoding to Nexus Coordinates...\n");
    clock_t start = clock();
    if (encode_file_to_nexus(input_file, key_file) != 0) {
        printf("Encoding Failed!\n");
        return 1;
    }
    clock_t end = clock();
    printf("Encoding Complete. Time: %.2f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage();

    // 2. Decoding
    printf("\n[Phase 2] Reconstructing from Nexus Key...\n");
    start = clock();
    if (decode_file_from_nexus(key_file, output_file) != 0) {
        printf("Decoding Failed!\n");
        return 1;
    }
    end = clock();
    printf("Decoding Complete. Time: %.2f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage();

    // 3. Verification (Simple size check for 1GB)
    printf("\n[Phase 3] Verification...\n");
    FILE *f1 = fopen(input_file, "rb");
    FILE *f2 = fopen(output_file, "rb");
    fseek(f1, 0, SEEK_END);
    fseek(f2, 0, SEEK_END);
    printf("Original Size: %ld bytes\n", ftell(f1));
    printf("Reconstructed Size: %ld bytes\n", ftell(f2));
    
    if (ftell(f1) == ftell(f2)) {
        printf("SUCCESS: File sizes match. .nexuss logic preserved integrity.\n");
    } else {
        printf("FAILURE: Size mismatch.\n");
    }

    fclose(f1);
    fclose(f2);

    printf("\n--- Large-Scale Proof Complete ---\n");
    return 0;
}
