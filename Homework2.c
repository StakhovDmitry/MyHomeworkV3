﻿#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    int n;
    int k = 0;
    int f = 0;
    int t = 1;
    bool flag = false;
    bool prov = false;
    scanf_s("%d", &n);
    int* arr = (int*)malloc(n * n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("%d:", i);

        for (int j = 0; j < n; j++) {
            scanf_s("%d", (arr + i * n + j));
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((i == j) && (arr[i * n + j] != 0)) {    //проверка диагонали
                prov = true;
            }

            if (arr[i * n + j] != arr[j * n + i]) {     //проверка симметричности относительно диагонали
                prov = true;
            }

            if ((arr[i * n + j] != 0) && (arr[i * n + j] != 1)) {      //проверка либо отсутвия ребра между вершинами, либо наличия лишь 1 таковой
                prov = true;
            }

            if (arr[i * n + j] == 1) {      //проверка того, что из каждой вершины выходит ровно 2 ребра
                k++;
            }

            if (k > 2) {
                prov = true;
            }
        }
        k = 0;
    }

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((arr[k * n + j] == 1) && (j != t) && (flag == false)) {     //проверка обходом
                t = k;
                k = j;
                flag = true;
            }
        }
        flag = false;

        if ((k == 0) && (i != n - 1)) {
            prov = true;
        }

        if ((i == n - 1) && (k != 0)) {
            prov = true;
        }
    }
    if (prov == false) {
        printf("simple cycle");
    }
    else
        printf("not a simple cycle");

 // визуализация //

    FILE* file;

    if ((file = fopen("Dot_file.txt", "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(file, "graph G{\n");

    for (int i = 0; i < n; i++) {

        for (int j = 0; j <= i; j++) {

            if (arr[i * n + j] != 0) {

                for (int g = 0; g < arr[i * n + j]; g++) {
                    fprintf(file, "%d -- %d;\n", (i + 1), (j + 1));
                }
            }
        }
    }
    fprintf(file, "}");
    fclose(file);
    system("dot C:\\Users\\User\\Desktop\\Алгоритмы\\MyHomework2V2\\Homework2\\Homework2\\Dot_file.txt -Tbmp -o Dot_file.bmp");
    system("rundll32 \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\User\\Desktop\\Алгоритмы\\MyHomework2V2\\Homework2\\Homework2\\Dot_file.bmp");
    return (0);
}
