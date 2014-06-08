#ifndef __MATRIX
#define __MATRIX
/**
 * This is a simple construction of a float matrix, with overload operators +,- and *
 */
class Matrix {
    // Public methods
    public:
        /**
         * Constructor
         *
         * @param int l Lines of Matrix
         * @param int c Colomuns of Matrix
         */
        Matrix(int l,int c);

        /**
         * Define a value
         *
         * @param float value Value to insert into matrix
         * @param int line    Line to insert
         * @param int column  Column to insert
         * @return void
         */
        void setValue(float value, int line, int column);

        /**
         * Obtain a value by line and column
         *
         * @param int line   Line to obtain
         * @param int column Column to obtain
         * @return float Value of position
         */
        float getValue(int line, int column);

        /**
         * Overload of * operator
         */
        Matrix operator*(const Matrix &value) const;

        /**
         * Overload of + operator
         */
        Matrix operator+(const Matrix &value) const;

        /**
         * Overload of - operator
         */
        Matrix operator-(const Matrix &value) const;

        /**
         * Obtain number of lines
         *
         * @return int
         */
        int getLines();

        /**
         * Obtain number of columns
         */
        int getColumns();

        /**
         * Show values in default output
         *
         * @return void
         */
        void print();

    // private attributes and methods
    private:
        /**
         * A vector of float to store matrix values
         */
        float* values;

        /**
         * Number of lines
         */
        int lines;

        /**
         * Number of columns
         */
        int columns;
};
#endif
