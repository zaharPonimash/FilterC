#pragma once
#ifndef POLYPHASE_FILTER_H
#define POLYPHASE_FILTER_H

// Структура PolyphaseFilter представляет собой полифазный фильтр
typedef struct {
    int numPhases;
    int phaseSize;  // Добавленное поле для хранения размера каждой фазы
    int* currentIndex;
    double* phases;
} PolyphaseFilter;

// Функция createPolyphaseFilter создает и инициализирует полифазный фильтр
PolyphaseFilter* createPolyphaseFilter(int numPhases, const double* coefficients, int coefficientsSize);

// Функция processSample обрабатывает входной сэмпл через полифазный фильтр и возвращает результат
double processSample(PolyphaseFilter* filter, double input);

// Функция incrementIndex увеличивает индекс текущей фазы в полифазном фильтре
void incrementIndex(PolyphaseFilter* filter, int phase);

// Функция освобождения памяти, выделенной для полифазного фильтра
void freePolyphaseFilter(PolyphaseFilter* filter);

#endif  // POLYPHASE_FILTER_H