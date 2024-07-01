#include "array_registers.h"

/* Fixed list of 16-bit write operations */
unsigned int write_operation_16[] = {
    0x80000206, 0x80000210, 0x80002700, 0x80002702, 0x80000206, 0x80000206, 0x80000206, 0x80000206,
    0x80000206, 0x80000206, 0x80000206, 0x80000206, 0x80000206, 0x80000206, 0x80000206, 0x80000206,
    0x80000206, 0x80000206, 0x80000206, 0x80000206
};
unsigned int data_to_write_16[] = {
    0x11111111, 0x44444444, 0x10FEDCBA, 0xAAAADCBA, 0x00000001, 0x00000002, 0x00000003, 0x00000004,
    0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009, 0x0000000A, 0x0000000B, 0x0000000C,
    0x0000000D, 0x0000000E, 0x0000000F, 0x00000000
};

/* Fixed list of 16-bit read operations */
unsigned int read_operation_16[] = {
    0x80002700, 0x80002702, 0x80002700, 0x80002702, 0x80002700, 0x80002702, 0x80002700, 0x80002702
};

/* Fixed list of 32-bit write operations */
unsigned int write_operation_32[] = {
    0x80000200, 0x80002000, 0x80002700
};
unsigned int data_to_write_32[] = {
    0x00000000, 0x87654321, 0x87654321
};

/* Fixed list of 32-bit read operations */
unsigned int read_operation_32[] = {
    0x80000204, 0x80000208, 0x8000020C, 0x80000210, 0x80000214, 0x80000204, 0x80000210, 0x80000214,
    0x80000218, 0x80000200, 0x80002000, 0x80002700, 0x80002700, 0x84800000, 0x84800010, 0x84000000,
    0x84000010, 0x8005C000, 0x80000218, 0x80000218, 0x80000218
};

#define NUM_WRITE_16 (sizeof(write_operation_16) / sizeof(write_operation_16[0]))
#define NUM_READ_16  (sizeof(read_operation_16) / sizeof(read_operation_16[0]))
#define NUM_WRITE_32 (sizeof(write_operation_32) / sizeof(write_operation_32[0]))
#define NUM_READ_32  (sizeof(read_operation_32) / sizeof(read_operation_32[0]))

/* Function: reg_main
 * ------------------------
 * This function performs the fixed 16-bit and 32-bit read and write operations on the registers.
 *
 * Parameters:
 *    None
 *
 * Return Value:
 *    DIR_SUCCESS - If the data is read/written successfully, the function will return DIR_SUCCESS.
 *    DIR_FAILURE - If the driver failed to open or unable to perform read/write operations, it will return DIR_FAILURE.
 */
int reg_main(void) {
    int l_hFile;         /* File descriptor for the device driver */
    int l_result;
    struct mem s_obj_mem; /* Structure to store memory operation details */

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_WRONLY);

    /* Check if the device driver was opened successfully */
    if (l_hFile == -1) {
        printf("open failed for %s\n", Driver_path);
        return DIR_FAILURE;
    }
    printf("Opened /dev/ModuleDiagnostic\n");

    /* Perform 16-bit read operations */
    for (size_t i = 0; i < NUM_READ_16; i++) {
        s_obj_mem.operation = OP_16BIT_READ; // 16-bit read operation
        s_obj_mem.address = read_operation_16[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("16-bit read failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        printf("16-bit Read: Address: 0x%08X Value: 0x%08X\n", s_obj_mem.address, l_result);
    }

    /* Perform 32-bit read operations */
    for (size_t i = 0; i < NUM_READ_32; i++) {
        s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
        s_obj_mem.address = read_operation_32[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("32-bit read failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        printf("32-bit Read: Address: 0x%08X Value: 0x%08X\n", s_obj_mem.address, l_result);
    }

    /* Perform 16-bit write operations */
    for (size_t i = 0; i < NUM_WRITE_16; i++) {
        s_obj_mem.operation = OP_16BIT_WRITE; // 16-bit write operation
        s_obj_mem.address = write_operation_16[i];
        s_obj_mem.value = data_to_write_16[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("16-bit write failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        printf("16-bit Write: Address: 0x%08X written value: 0x%08X\n", s_obj_mem.address, s_obj_mem.value);
    }
   
    /* Perform 16-bit read operations */
    for (size_t i = 0; i < NUM_READ_16; i++) {
        s_obj_mem.operation = OP_16BIT_READ; // 16-bit read operation
        s_obj_mem.address = read_operation_16[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("16-bit read failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        printf("16-bit Read: Address: 0x%08X Value: 0x%08X\n", s_obj_mem.address, l_result);
    }

    /* Perform 32-bit write operations */
    for (size_t i = 0; i < NUM_WRITE_32; i++) {
        s_obj_mem.operation = OP_32BIT_WRITE; // 32-bit write operation
        s_obj_mem.address = write_operation_32[i];
        s_obj_mem.value = data_to_write_32[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("32-bit write failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        printf("32-bit Write: Address: 0x%08X written value: 0x%08X\n", s_obj_mem.address, s_obj_mem.value);
    }

    /* Perform 32-bit read operations */
    for (size_t i = 0; i < NUM_READ_32; i++) {
        s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
        s_obj_mem.address = read_operation_32[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("32-bit read failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        printf("32-bit Read: Address: 0x%08X Value: 0x%08X\n", s_obj_mem.address, l_result);
    }

    /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}

