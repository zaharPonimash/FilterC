#pragma once
#include "polyphase_filter.h"
#include <stdio.h>
#include <stdlib.h>

PolyphaseFilter* createPolyphaseFilter(int numPhases, const double* coefficients, int coefficientsSize) {
    // Проверка на валидность входных параметров
    if (numPhases <= 0 || coefficientsSize <= 0 || coefficients == NULL || coefficientsSize % numPhases != 0) {
        fprintf(stderr, "Error: Invalid input parameters.\n");
        return NULL;
    }

    // Выделение памяти для структуры PolyphaseFilter
    PolyphaseFilter* filter = (PolyphaseFilter*)malloc(sizeof(PolyphaseFilter));
    if (filter == NULL) {
        perror("Error: Unable to allocate memory for PolyphaseFilter");
        return NULL;
    }

    filter->numPhases = numPhases;
    filter->phaseSize = coefficientsSize / numPhases;
    filter->currentIndex = (int*)malloc(numPhases * sizeof(int));
    filter->phases = (double*)malloc(coefficientsSize * sizeof(double));

    if (filter->currentIndex == NULL || filter->phases == NULL) {
        free(filter->currentIndex);
        free(filter->phases);
        free(filter);
        perror("Error: Unable to allocate memory for filter components");
        return NULL;
    }

    // Копирование коэффициентов и инициализация индексов
    memcpy(filter->phases, coefficients, coefficientsSize * sizeof(double));
    for (int i = 0; i < numPhases; ++i) {
        filter->currentIndex[i] = 0;
    }

    return filter;
}

double processSample(PolyphaseFilter* filter, double input) {
    if (filter == NULL) {
        fprintf(stderr, "Error: Filter is NULL.\n");
        return 0.0;
    }

    double output = 0.0;
    for (int i = 0; i < filter->numPhases; ++i) {
        int index = filter->currentIndex[i];
        output += filter->phases[i * filter->phaseSize + index] * input;
        incrementIndex(filter, i);
    }
    return output;
}

void incrementIndex(PolyphaseFilter* filter, int phase) {
    if (filter == NULL || phase < 0 || phase >= filter->numPhases) {
        return;
    }

    filter->currentIndex[phase] = (filter->currentIndex[phase] + 1) % filter->phaseSize;
}

void freePolyphaseFilter(PolyphaseFilter* filter) {
    if (filter == NULL) {
        return;
    }

    free(filter->currentIndex);
    free(filter->phases);
    free(filter);
}
