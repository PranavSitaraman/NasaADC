/*
 * File: heightmap.c
 * Team Ad Lunam
 * NASA ADC 2022-2023
 */

// all data is in meters (m)

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265
#define RAD(x) ((PI / 180) * x)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

const int SIZE = 4000;
const double lunar_radius = 1737.4 * 1000; // lunar radius in meters
double longitude[4000 * 4000], latitude[4000 * 4000], height[4000 * 4000];
double points[4000 * 4000][3];

int main()
{
    time_t start_time = time(NULL);
    printf("STARTED READING | %lld | %lld \n", 0, 0);

    // read longitude values
    FILE* longFile = fopen("data/longitude.csv", "r");
    if (longFile == NULL) {
        printf("LONGITUDE CSV ERROR\n");
        return 1;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            int index = i * SIZE + j;
            fscanf(longFile, "%lf,", &longitude[index]);
        }
        fscanf(longFile, "%lf\n", &longitude[i * SIZE + SIZE - 1]);
    }
    fclose(longFile);
    time_t long_time = time(NULL);
    printf("READ LONGITUDE | %lld | %lld \n", long_time - start_time, long_time - start_time);

    // read latitude values
    FILE* latFile = fopen("data/latitude.csv", "r");
    if (latFile == NULL) {
        printf("LATITUDE CSV ERROR\n");
        return 1;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            int index = i * SIZE + j;
            fscanf(latFile, "%lf,", &latitude[index]);
        }
        fscanf(latFile, "%lf\n", &latitude[i * SIZE + SIZE - 1]);
    }
    fclose(latFile);
    time_t lat_time = time(NULL);
    printf("READ LATITUDE | %lld | %lld \n", lat_time - start_time, lat_time - long_time);

    // read height values
    FILE* heightFile = fopen("data/height.csv", "r");
    if (heightFile == NULL) {
        printf("HEIGHT CSV ERROR\n");
        return 1;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            int index = i * SIZE + j;
            fscanf(heightFile, "%lf,", &height[index]);
        }
        fscanf(heightFile, "%lf\n", &height[i * SIZE + SIZE - 1]);
    }
    fclose(heightFile);
    time_t hei_time = time(NULL);
    printf("READ HEIGHT | %lld | %lld \n", hei_time - start_time, hei_time - lat_time);

    // convert spherical coordinates to point cloud
    double minZ = INFINITY, maxZ = -INFINITY;
    for (int i = 0; i < SIZE * SIZE; i++) {
        double radius = lunar_radius + height[i];
        double x = radius * cos(RAD(latitude[i])) * cos(RAD(longitude[i]));
        double y = radius * cos(RAD(latitude[i])) * sin(RAD(longitude[i]));
        double z = radius * sin(RAD(latitude[i]));
        points[i][0] = x;
        points[i][1] = y;
        points[i][2] = z;
        minZ = MIN(minZ, z);
        maxZ = MAX(maxZ, z);
    }
    time_t calc_time = time(NULL);
    printf("CALCULATED VALUES | %lld | %lld \n", calc_time - start_time, calc_time - hei_time);
    printf("MIN: %lf m\nMAX: %lf m\n", minZ, maxZ);

    // write point cloud data to .xyz file
    FILE* pointFile = fopen("data/points.xyz", "w");
    if (pointFile == NULL) {
        printf("ERROR WRITING POINT CLOUD\n");
        return 1;
    }
    for (int i = 0; i < SIZE * SIZE; i++) {
        points[i][2] += fabs(minZ);
        fprintf(pointFile, "%lf %lf %lf\n", points[i][0], points[i][1], points[i][2]);
    }
    fclose(pointFile);
    time_t xyz_time = time(NULL);
    printf("WROTE POINT CLOUD | %lld | %lld \n", xyz_time - start_time, xyz_time - calc_time);

    // parallelly write z-value to grid and write 16 bit scaled value to .pgm image file
    FILE* gridFile = fopen("data/grid.txt", "w");
    FILE* imageFile = fopen("data/heightmap.pgm", "wb");
    double scale_value = fabs(maxZ - minZ);
    if (gridFile == NULL) {
        printf("ERROR WRITING GRID DATA\n");
        return 1;
    }
    if (imageFile == NULL) {
        printf("ERROR WRITING IMAGE DATA\n");
        return 1;
    }
    fprintf(imageFile, "P5\n# NASA ADC\n%i %i\n65535\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int n = i * SIZE + j;
            fprintf(gridFile, "%lf ", points[n][2]);
            uint16_t color = (uint16_t)((1.0 - (points[n][2] / fabs(maxZ - minZ))) * 0xFFFF);
            uint16_t swapped = ((color << 8) | (color >> 8));
            fwrite(&swapped, sizeof(uint16_t), 1, imageFile);
        }
        fprintf(gridFile, "\n");
    }
    fclose(gridFile);
    fclose(imageFile);
    time_t write_time = time(NULL);
    printf("WROTE DATA | %lld | %lld \n", write_time - start_time, write_time - calc_time);

    // use ImageMagick to convert .pgm to .png format
    system("magick data\\heightmap.pgm data\\heightmap.png");
    time_t done_time = time(NULL);
    printf("DONE | %lld | %lld\n", done_time - start_time, done_time - write_time);

    return 0;
}