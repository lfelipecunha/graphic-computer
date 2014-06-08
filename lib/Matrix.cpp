#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

// contructor
Matrix::Matrix(int l, int c) {
    lines = l;
    columns = c;
    values = (float*) malloc(sizeof(float*) * lines * columns);
}

// define value of position
void Matrix::setValue(float value, int line, int column) {
    if ( (line * columns + column) >= (lines * columns) ) {
        printf("setValue\n");
        throw;
    }

    values[line * columns + column] = value;
}

// obtain value by position
float Matrix::getValue(int line, int column) {
    if ( (line * columns + column) >= (lines * columns) ) {
        printf("getValue\n");
        throw;
    }
    return values[line * columns + column];
}

// obtain number of positions
int Matrix::getLines() {
    return lines;
}


// obtain number of columns
int Matrix::getColumns() {
    return columns;
}

// overload *
Matrix Matrix::operator*(const Matrix &value) const {
    Matrix actual = *this;
    Matrix other = value;
    if (actual.getColumns() != other.getLines()) {
        throw;
    }

    Matrix m(actual.getLines(),other.getColumns());

    for (int line=0; line < actual.getLines(); line++) {
        for (int i = 0; i < other.getColumns(); i++) {
            float sum = 0;
            for (int column=0; column < actual.getColumns(); column++) {
                sum += (actual.getValue(line,column)) *  (other.getValue(column,i));
            }
            m.setValue(sum,line,i);
        }
    }
    return m;
}

// overload +
Matrix Matrix::operator+(const Matrix &value) const {
    Matrix actual = *this;
    Matrix other = value;
    if (actual.getLines() != other.getLines() || actual.getColumns() != other.getColumns()) {
        throw;
    }

    Matrix m(actual.getLines(),actual.getColumns());

    for (int line=0; line < actual.getLines(); line++) {
        for (int column=0; column < actual.getColumns(); column++) {
            float sum = actual.getValue(line,column) +  (other.getValue(line,column));
            m.setValue(sum,line,column);
        }
    }
    return m;
}

// overload -
Matrix Matrix::operator-(const Matrix &value) const {
    Matrix actual = *this;
    Matrix other = value;
    if (actual.getLines() != other.getLines() || actual.getColumns() != other.getColumns()) {
        throw;
    }

    Matrix m(actual.getLines(),actual.getColumns());

    for (int line=0; line < actual.getLines(); line++) {
        for (int column=0; column < actual.getColumns(); column++) {
            float sum = actual.getValue(line,column) -  (other.getValue(line,column));
            m.setValue(sum,line,column);
        }
    }
    return m;
}

// show formatted values in default output
void Matrix::print() {
    for (int i=0; i<getLines();i++) {
        for (int j=0; j<getColumns();j++) {
            printf("%f\t",getValue(i,j));
        }
        printf("\n");
    }
}
