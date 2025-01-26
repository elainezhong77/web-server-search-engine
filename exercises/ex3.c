// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct Point3d {
uint16_t x, y, z;
} Point3d;

Point3d* AllocatePoint3d(uint16_t x1, uint16_t y1, uint16_t z1);

int main(int argc, char **argv) {
    Point3d* point3d_ptr = AllocatePoint3d(1, 2, 3);

    if (point3d_ptr == NULL) {
        printf("Could not allocated space for a Point3d.\n");
        exit(EXIT_FAILURE);
    }

    if (point3d_ptr -> x != 1) {
        printf("The x coordinate value is incorrect.\n");
        free(point3d_ptr);
        exit(EXIT_FAILURE);
    }
    if (point3d_ptr -> y != 2) {
        printf("The y coordinate value is incorrect.\n");
        free(point3d_ptr);
        exit(EXIT_FAILURE);
    }
    if (point3d_ptr -> z != 3) {
        printf("The z coordinate value is incorrect.\n");
        free(point3d_ptr);
        exit(EXIT_FAILURE);
    }
    free(point3d_ptr);
    return EXIT_SUCCESS;
}

Point3d* AllocatePoint3d(uint16_t x1, uint16_t y1, uint16_t z1) {
    Point3d* pointer =(Point3d*) malloc(sizeof(Point3d));

    if (pointer != NULL) {
        pointer -> x = x1;
        pointer -> y = y1;
        pointer -> z = z1;
    }
    return pointer;
}
