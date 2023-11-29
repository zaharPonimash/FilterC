#pragma once
#ifndef POLYPHASE_FILTER_H
#define POLYPHASE_FILTER_H

// ��������� PolyphaseFilter ������������ ����� ���������� ������
typedef struct {
    int numPhases;
    int phaseSize;  // ����������� ���� ��� �������� ������� ������ ����
    int* currentIndex;
    double* phases;
} PolyphaseFilter;

// ������� createPolyphaseFilter ������� � �������������� ���������� ������
PolyphaseFilter* createPolyphaseFilter(int numPhases, const double* coefficients, int coefficientsSize);

// ������� processSample ������������ ������� ����� ����� ���������� ������ � ���������� ���������
double processSample(PolyphaseFilter* filter, double input);

// ������� incrementIndex ����������� ������ ������� ���� � ���������� �������
void incrementIndex(PolyphaseFilter* filter, int phase);

// ������� ������������ ������, ���������� ��� ����������� �������
void freePolyphaseFilter(PolyphaseFilter* filter);

#endif  // POLYPHASE_FILTER_H