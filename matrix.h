#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <stdexcept>
#include <QVector3D>

class Matrix
{
public:
    Matrix(size_t dimx, size_t dimy);
    explicit Matrix(const Matrix &other);
    Matrix(Matrix &&other);
    explicit Matrix(const QVector3D &vec);
    Matrix(const QVector3D &&vec);
    ~Matrix();

    void fill(double value);
    void loadIdentity();
    QVector3D toVector() throw(std::out_of_range);

    double &at(size_t x, size_t y) throw(std::out_of_range);

    Matrix &operator=(const Matrix &other);
    Matrix &operator+=(const Matrix &other) throw(std::invalid_argument);
    Matrix &operator-=(const Matrix &other) throw(std::invalid_argument);
    Matrix &operator*=(double scalar);
    Matrix &operator/=(double scalar);
    Matrix &operator*=(Matrix &other) throw(std::invalid_argument);
    Matrix &operator*=(Matrix &&other) throw(std::invalid_argument);

    Matrix operator+(const Matrix &other) throw(std::invalid_argument);
    Matrix operator*(double scalar);
    Matrix operator*(Matrix &other) throw(std::invalid_argument);
    Matrix operator*(Matrix &&other) throw(std::invalid_argument);

    Matrix &transpose() throw(std::invalid_argument);
    Matrix &reverse() throw(std::invalid_argument);
    double determinator() throw(std::invalid_argument);

    Matrix transposed() throw(std::invalid_argument);
    Matrix reversed() throw(std::invalid_argument);

#define DEBUG
#ifdef DEBUG
    void print();
#endif

private:
    size_t sizex;
    size_t sizey;
    double *data;
};

#endif // MATRIX_H
