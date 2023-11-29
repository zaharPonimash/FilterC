#include "polyphase_filter.h"
#include <stdio.h>

int main() {
    // Сглаживающий фильтр
    double coefficients[] = { 0.1, 0.15, 0.3, 0.7, 1, 0.7, 0.3, 0.15, 0.1 };
    // Нормировка коэф фильтра
    double sum = 0;
    for (int i = 0; i < 9; i++)  sum += coefficients[i];
    for (int i = 0; i < 9; i++)  coefficients[i] /= sum;

    int numPhases = 3;

    PolyphaseFilter* filter = createPolyphaseFilter(numPhases, coefficients, sizeof(coefficients) / sizeof(coefficients[0]));

    double inputSignal[] = { 1.0, 1.0, 13., 1.00, 13.0, 1.0, 1.0 };
    int inputSignalSize = sizeof(inputSignal) / sizeof(inputSignal[0]);
    for (int i = 0; i < inputSignalSize; ++i) {
        double output = processSample(filter, inputSignal[i]);
        printf("Input: %.2f, Output: %.2f\n", inputSignal[i], output);
    }

    freePolyphaseFilter(filter);

    return 0;
}