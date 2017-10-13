//
//  common_matrix.h
//  opencv
//
//  Created by pengsida on 2017/10/6.
//  Copyright © 2017年 pengsida. All rights reserved.
//

#ifndef cm_vec_mat_h
#define cm_vec_mat_h

#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

namespace cm {
    struct mat_sz;
    template <typename T>
    class matrix;

    template <typename T>
    class vector {
    private:
        int rows;
        T* vec;
        
    public:
        typedef T value_type;
        
    public:
        vector();
        explicit vector(int rows);
        vector(int rows, const T& a);
        vector(int rows, const T* array);
        vector(const vector<T>& rhs);
        vector(const initializer_list<T>& list);
        vector& operator=(const vector& rhs);
        
        ~vector();
        
        T dot(const vector<T>& rhs) const;
        matrix<T> operator*(const matrix<T>& rhs) const;
        vector<T> operator*(const T& a) const;
        template <typename type>
        friend vector<type> operator*(const type& a, const vector<type>& rhs);
        vector<T> operator+(const vector<T>& rhs) const;
        
        inline T& operator[](const int i);
        inline const T& operator[](const int i) const;
        
        inline bool empty() const { return rows == 0; }
        inline int size() const { return rows; }
        void resize(int new_rows);
        void assign(int new_rows, const T& a);
        
        void print() const;
        template <typename type>
        friend ostream& operator<<(ostream& os, const vector<type>& rhs);
        
    private:
        void clear();
    };

    struct mat_sz {
        size_t rows;
        size_t cols;
        
        mat_sz(size_t rows, size_t cols): rows(rows), cols(cols) {}
        mat_sz(const mat_sz& sz): rows(sz.rows), cols(sz.cols) {}
    };

    template <typename T>
    class matrix {
    private:
        int rows;
        int cols;
        T** mat;
        
    public:
        typedef T value_type;
        
    public:
        static matrix<T> diag(int dim, const T& a);
        static void diag(int dim, const T& a, matrix<T>& new_mat);
        
    public:
        matrix();
        matrix(int rows, int cols);
        matrix(int rows, int cols, const T& a);
        matrix(int rows, int cols, const T* array);
        matrix(const matrix<T>& rhs);
        matrix(const initializer_list<initializer_list<T>>& list);
        matrix& operator=(const matrix& rhs);
        
        ~matrix();
        
        matrix<T> operator*(const matrix<T>& rhs) const;
        matrix<T> operator*(const T& a) const;
        template <typename type>
        friend matrix<type> operator*(const type& a, const matrix<type>& rhs);
        
        inline T*& operator[](const int i) { return mat[i]; }
        inline const T* operator[](const int i) const { return mat[i]; }
        
        inline bool empty() const { return rows == 0 && cols == 0; }
        inline int nrows() const { return rows; }
        inline int ncols() const { return cols; }
        void resize(int new_rows, int new_cols);
        void assign(int new_rows, int new_cols, const T& a);
        
        void print() const;
        template <typename type>
        friend ostream& operator<<(ostream& os, const matrix<type>& rhs);
        
        void swap_row(int i, int j);
        template <typename type>
        void divide_row(int row, type num);
        template <typename type>
        void combine_row(int dst_row, int other_row, type factor);
        
    private:
        void clear();
        void resize_row(T* row_arr, int i, int new_cols) const;
        void print_row(T* row_arr) const;
        void print_row(ostream& os, T* row_arr) const;
    };

    template <typename T>
    vector<T>::vector(): rows(0), vec(NULL) { }

    template <typename T>
    vector<T>::vector(int rows): rows(rows), vec(new T[rows]()) { }

    template <typename T>
    vector<T>::vector(int rows, const T& a): rows(rows), vec(new T[rows]) {
        for (int i = 0; i < rows; i++)
            vec[i] = a;
    }

    template <typename T>
    vector<T>::vector(int rows, const T* array): rows(rows), vec(new T[rows]) {
        for (int i = 0; i < rows; i++)
            vec[i] = array[i];
    }

    template <typename T>
    vector<T>::vector(const vector<T>& rhs): rows(rhs.rows), vec(new T[rhs.rows]) {
        for (int i = 0; i < rows; i++)
            vec[i] = rhs[i];
    }

    template <typename T>
    vector<T>::vector(const initializer_list<T>& list): rows((int)list.size()), vec(new T[list.size()]) {
        auto begin = list.begin();
        auto end = list.end();
        
        int i = 0;
        for (; begin != end; begin++)
            vec[i++] = *begin;
    }

    template <typename T>
    vector<T>& vector<T>::operator=(const vector<T>& rhs) {
        if (&rhs == this)
            return *this;
        clear();
        
        rows = rhs.rows;
        vec = new T[rows];
        for (int i = 0; i < rows; i++)
            vec[i] = rhs.vec[i];
        
        return *this;
    }

    template <typename T>
    vector<T>::~vector() {
        clear();
    }
    
    template <typename T>
    T vector<T>::dot(const vector<T>& rhs) const {
        cout << "This data type haven't been implemented" << endl;
        exit(1);
    }
    
    template <>
    int vector<int>::dot(const vector<int>& rhs) const {
        if (size() != rhs.size()) {
            cout << "The vectors' length is not equal" << endl;
            exit(1);
        }
        
        int sum = 0;
        for (int i = 0; i < rows; i++)
            sum = sum + vec[i] * rhs.vec[i];
        
        return sum;
    }
    
    template <>
    float vector<float>::dot(const vector<float>& rhs) const {
        if (size() != rhs.size()) {
            cout << "The vectors' length is not equal" << endl;
            exit(1);
        }
        
        float sum = 0;
        for (int i = 0; i < rows; i++)
            sum = sum + vec[i] * rhs.vec[i];
        
        return sum;
    }
    
    template <>
    double vector<double>::dot(const vector<double>& rhs) const {
        if (size() != rhs.size()) {
            cout << "The vectors' length is not equal" << endl;
            exit(1);
        }
        
        double sum = 0;
        for (int i = 0; i < rows; i++)
            sum = sum + vec[i] * rhs.vec[i];
        
        return sum;
    }
    
    template <typename T>
    matrix<T> vector<T>::operator*(const matrix<T>& rhs) const {
        cout << "This data type haven't been implemented" << endl;
        exit(1);
    }
    
    template <>
    matrix<int> vector<int>::operator*(const matrix<int>& rhs) const {
        if (rhs.nrows() != 1) {
            cout << "The input matrix is unexpected" << endl;
            exit(1);
        }
        
        int new_rows = rows;
        int new_cols = rhs.ncols();
        matrix<int> new_mat(new_rows, new_cols);
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++)
                new_mat[i][j] = vec[i] * rhs[0][j];
        }
        
        return new_mat;
    }
    
    template <>
    matrix<float> vector<float>::operator*(const matrix<float>& rhs) const {
        if (rhs.nrows() != 1) {
            cout << "The input matrix is unexpected" << endl;
            exit(1);
        }
        
        int new_rows = rows;
        int new_cols = rhs.ncols();
        matrix<float> new_mat(new_rows, new_cols);
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++)
                new_mat[i][j] = vec[i] * rhs[0][j];
        }
        
        return new_mat;
    }
    
    template <>
    matrix<double> vector<double>::operator*(const matrix<double>& rhs) const {
        if (rhs.nrows() != 1) {
            cout << "The input matrix is unexpected" << endl;
            exit(1);
        }
        
        int new_rows = rows;
        int new_cols = rhs.ncols();
        matrix<double> new_mat(new_rows, new_cols);
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++)
                new_mat[i][j] = vec[i] * rhs[0][j];
        }
        
        return new_mat;
    }
    
    template <typename T>
    vector<T> vector<T>::operator*(const T& a) const {
        cout << "This data type haven't been implemented" << endl;
        exit(1);
    }
    
    template <>
    vector<int> vector<int>::operator*(const int& a) const {
        vector<int> new_vec(rows);
        
        for (int i = 0; i < rows; i++)
            new_vec[i] = vec[i] * a;
        
        return new_vec;
    }
    
    template <>
    vector<float> vector<float>::operator*(const float& a) const {
        vector<float> new_vec(rows);
        
        for (int i = 0; i < rows; i++)
            new_vec[i] = vec[i] * a;
        
        return new_vec;
    }
    
    template <>
    vector<double> vector<double>::operator*(const double& a) const {
        vector<double> new_vec(rows);
        
        for (int i = 0; i < rows; i++)
            new_vec[i] = vec[i] * a;
        
        return new_vec;
    }
    
    template <typename T>
    vector<T> operator*(const T& a, const vector<T>& rhs) {
        cout << "This data type haven't been implemented" << endl;
        exit(1);
    }
    
    template <>
    vector<int> operator*(const int& a, const vector<int>& rhs) {
        int rows = rhs.size();
        vector<int> new_vec(rows);
        
        for (int i = 0; i < rows; i++)
            new_vec[i] = rhs[i] * a;
        
        return new_vec;
    }
    
    template <>
    vector<float> operator*(const float& a, const vector<float>& rhs) {
        int rows = rhs.size();
        vector<float> new_vec(rows);
        
        for (int i = 0; i < rows; i++)
            new_vec[i] = rhs[i] * a;
        
        return new_vec;
    }
    
    template <>
    vector<double> operator*(const double& a, const vector<double>& rhs) {
        int rows = rhs.size();
        vector<double> new_vec(rows);
        
        for (int i = 0; i < rows; i++)
            new_vec[i] = rhs[i] * a;
        
        return new_vec;
    }
    
    template <typename T>
    vector<T> vector<T>::operator+(const vector<T>& rhs) const {
        if (size() != rhs.size())
            throw "Two vectors' dimension don't coincide";
        vector<T> add_vec(size());
        
        for (int i = 0; i < rows; i++)
            add_vec[i] = vec[i] + rhs.vec[i];
        
        return add_vec;
    }

    template <typename T>
    T& vector<T>::operator[](const int i) {
        return vec[i];
    }

    template <typename T>
    const T& vector<T>::operator[](const int i) const {
        return vec[i];
    }

    template <typename T>
    void vector<T>::resize(int new_rows) {
        T* new_vec = new T[new_rows];
        
        if (rows < new_rows) {
            for (int i = 0; i < rows; i++)
                new_vec[i] = vec[i];
            for (int i = rows; i < new_rows; i++)
                new_vec[i] = T();
        } else {
            for (int i = 0; i < new_rows; i++)
                new_vec[i] = vec[i];
        }
        
        rows = new_rows;
        delete[] vec;
        vec = new_vec;
    }

    template <typename T>
    void vector<T>::assign(int new_rows, const T& a) {
        T* new_vec = new T[new_rows];
        
        for (int i = 0; i < new_rows; i++)
            new_vec[i] = a;
        
        rows = new_rows;
        delete[] vec;
        vec = new_vec;
    }

    template <typename T>
    void vector<T>::print() const {
        if (empty()) {
            cout << "it's an empty vector" << endl;
            exit(1);
        }
        
        if (rows == 1) {
            cout << "[" << *vec << "]" << endl;
            return;
        }
        
        int i = 0;
        cout << "[" << vec[i++] << endl;
        for (; i + 1 < rows; i++)
            cout << " " << vec[i] << endl;
        cout << " " << vec[i] << "]" << endl;
    }

    template <typename T>
    ostream& operator<<(ostream& os, const vector<T>& rhs) {
        if (rhs.empty()) {
            cout << "it's an empty vector" << endl;
            exit(1);
        }
        
        if (rhs.rows == 1) {
            os << "[" << *(rhs.vec) << "]";
            return os;
        }
        
        int i = 0;
        os << "[" << rhs.vec[i++] << endl;
        for (; i + 1 < rhs.rows; i++)
            os << " " << rhs.vec[i] << endl;
        os << " " << rhs.vec[i] << "]";
        
        return os;
    }

    template <typename T>
    void vector<T>::clear() {
        if (vec)
            delete[] vec;
        vec = NULL;
        rows = 0;
    }
    
    template <typename T>
    matrix<T> matrix<T>::diag(int dim, const T& a) {
        matrix<T> mat(dim, dim);
        
        for (int i = 0; i < dim; i++)
            mat[i][i] = a;
        
        return mat;
    }
    
    template <typename T>
    void matrix<T>::diag(int dim, const T& a, matrix<T>& new_mat) {
        new_mat.assign(dim, dim, 0);
        
        for (int i = 0; i < dim; i++)
            new_mat[i][i] = a;
    }
    
    template <typename T>
    matrix<T>::matrix(): rows(0), cols(0), mat(NULL) { }
    
    template <typename T>
    matrix<T>::matrix(int rows, int cols): rows(rows), cols(cols) {
        mat = new T*[rows];
        
        for (int i = 0; i < cols; i++)
            mat[i] = new T[cols]();
    }
    
    template <typename T>
    matrix<T>::matrix(int rows, int cols, const T& a): rows(rows), cols(cols) {
        mat = new T*[rows];
        
        for (int i = 0; i < cols; i++) {
            mat[i] = new T[cols];
            
            for (int j = 0; j < cols; j++)
                mat[i][j] = a;
        }
    }
    
    template <typename T>
    matrix<T>::matrix(int rows, int cols, const T* array): rows(rows), cols(cols) {
        mat = new T*[rows];
        
        for (int i = 0; i < cols; i++) {
            mat[i] = new T[cols];
            
            for (int j = 0; j < cols; j++)
                mat[i][j] = array[i * cols + j];
        }
    }
    
    template <typename T>
    matrix<T>::matrix(const matrix<T>& rhs): rows(rhs.rows), cols(rhs.cols) {
        mat = new T*[rows];
        
        for (int i = 0; i < cols; i++) {
            mat[i] = new T[cols];
            
            for (int j = 0; j < cols; j++)
                mat[i][j] = rhs.mat[i][j];
        }
    }
    
    template <typename T>
    matrix<T>::matrix(const initializer_list<initializer_list<T>>& list): rows((int)list.size()) {
        auto row_beg = list.begin();
        auto row_end = list.end();
        
        cols = (int)row_beg->size();
        mat = new T*[rows];
        int i = 0;
        for (; row_beg != row_end; row_beg++, i++) {
            if (cols != row_beg->size()) {
                cout << "The input parameter is unexpected" << endl;
                exit(1);
            }
            
            mat[i] = new T[cols];
            auto col_beg = row_beg->begin();
            auto col_end = row_beg->end();
            for (int j = 0; col_beg != col_end; col_beg++, j++)
                mat[i][j] = *col_beg;
        }
    }
    
    template <typename T>
    matrix<T>& matrix<T>::operator=(const matrix<T>& rhs) {
        if (&rhs == this)
            return *this;
        
        clear();
        rows = rhs.rows;
        cols = rhs.cols;
        mat = new T*[rows];
        for (int i = 0; i < rows; i++) {
            mat[i] = new T[cols];
            
            for (int j = 0; j < cols; j++)
                mat[i][j] = rhs.mat[i][j];
        }
        
        return *this;
    }
    
    template <typename T>
    matrix<T>::~matrix() {
        clear();
    }
    
    template <typename T>
    matrix<T> matrix<T>::operator*(const matrix<T>& rhs) const {
        cout << "This data type haven't been implemented" << endl;
        exit(1);
    }
    
    template <>
    matrix<int> matrix<int>::operator*(const matrix<int>& rhs) const {
        if (ncols() != rhs.nrows()) {
            cout << "The input parameters are unexpected" << endl;
            exit(1);
        }
        
        int new_rows = nrows();
        int new_cols = rhs.ncols();
        matrix<int> new_mat(new_rows, new_cols);
        
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++)
                    sum = sum + mat[i][k] * rhs.mat[k][j];
                new_mat[i][j] = sum;
            }
        }
        
        return new_mat;
    }
    
    template <>
    matrix<float> matrix<float>::operator*(const matrix<float>& rhs) const {
        if (ncols() != rhs.nrows()) {
            cout << "The input parameters are unexpected" << endl;
            exit(1);
        }
        
        int new_rows = nrows();
        int new_cols = rhs.ncols();
        matrix<float> new_mat(new_rows, new_cols);
        
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++) {
                float sum = 0;
                for (int k = 0; k < cols; k++)
                    sum = sum + mat[i][k] * rhs.mat[k][j];
                new_mat[i][j] = sum;
            }
        }
        
        return new_mat;
    }
    
    template <>
    matrix<double> matrix<double>::operator*(const matrix<double>& rhs) const {
        if (ncols() != rhs.nrows()) {
            cout << "The input parameters are unexpected" << endl;
            exit(1);
        }
        
        int new_rows = nrows();
        int new_cols = rhs.ncols();
        matrix<double> new_mat(new_rows, new_cols);
        
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++) {
                float sum = 0;
                for (int k = 0; k < cols; k++)
                    sum = sum + mat[i][k] * rhs.mat[k][j];
                new_mat[i][j] = sum;
            }
        }
        
        return new_mat;
    }
    
    template <typename T>
    matrix<T> matrix<T>::operator*(const T& a) const {
        cout << "This data type haven't been implemented" << endl;
        exit(1);
    }
    
    template <>
    matrix<int> matrix<int>::operator*(const int& a) const {
        matrix<int> new_mat(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                new_mat[i][j] = mat[i][j] * a;
        }
        
        return new_mat;
    }
    
    template <>
    matrix<float> matrix<float>::operator*(const float& a) const {
        matrix<float> new_mat(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                new_mat[i][j] = mat[i][j] * a;
        }
        
        return new_mat;
    }
    
    template <>
    matrix<double> matrix<double>::operator*(const double& a) const {
        matrix<double> new_mat(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                new_mat[i][j] = mat[i][j] * a;
        }
        
        return new_mat;
    }
    
    template <typename T>
    matrix<T> operator*(const T& a, const matrix<T>& rhs) {
        cout << "This data type haven't been implemented" << endl;
        exit(1);
    }
    
    template <>
    matrix<int> operator*(const int& a, const matrix<int>& rhs) {
        int rows = rhs.nrows();
        int cols = rhs.ncols();
        matrix<int> new_mat(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                new_mat[i][j] = rhs[i][j] * a;
        }
        
        return new_mat;
    }
    
    template <>
    matrix<float> operator*(const float& a, const matrix<float>& rhs) {
        int rows = rhs.nrows();
        int cols = rhs.ncols();
        matrix<float> new_mat(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                new_mat[i][j] = rhs[i][j] * a;
        }
        
        return new_mat;
    }
    
    template <>
    matrix<double> operator*(const double& a, const matrix<double>& rhs) {
        int rows = rhs.nrows();
        int cols = rhs.ncols();
        matrix<double> new_mat(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                new_mat[i][j] = rhs[i][j] * a;
        }
        
        return new_mat;
    }
    
    template <typename T>
    void matrix<T>::resize(int new_rows, int new_cols) {
        T** new_mat = new T*[new_rows];
        
        if (rows < new_rows) {
            int i = 0;
            for (; i < rows; i++) {
                new_mat[i] = new T[new_cols];
                resize_row(new_mat[i], i, new_cols);
            }
            for (; i < new_rows; i++) {
                new_mat[i] = new T[new_cols];
                for (int j = 0; j < new_cols; j++)
                    new_mat[i][j] = T();
            }
        } else {
            for (int i = 0; i < new_rows; i++) {
                new_mat[i] = new T[new_cols];
                resize_row(new_mat[i], i, new_cols);
            }
        }
        
        clear();
        mat = new_mat;
        rows = new_rows;
        cols = new_cols;
    }
    
    template <typename T>
    void matrix<T>::assign(int new_rows, int new_cols, const T& a) {
        T** new_mat = new T*[new_rows];
        
        for (int i = 0; i < new_rows; i++) {
            new_mat[i] = new T[new_cols];
            
            for (int j = 0; j < new_cols; j++)
                new_mat[i][j] = a;
        }
        
        clear();
        mat = new_mat;
        rows = new_rows;
        cols = new_cols;
    }
    
    template <typename T>
    void matrix<T>::print() const {
        if (empty()) {
            cout << "it's an empty matrix" << endl;
            exit(1);
        }
        
        if (rows == 1) {
            cout << "[";
            print_row(mat[0]);
            cout << "]" << endl;
            return;
        }
        
        int i = 0;
        cout << "[";
        print_row(mat[i++]);
        cout << endl;
        for (; i + 1 < rows; i++) {
            cout << " ";
            print_row(mat[i]);
            cout << endl;
        }
        cout << " ";
        print_row(mat[i++]);
        cout << "]" << endl;
    }
    
    template <typename T>
    ostream& operator<<(ostream& os, const matrix<T>& rhs) {
        if (rhs.empty()) {
            cout << "it's an empty matrix" << endl;
            exit(1);
        }
        
        if (rhs.rows == 1) {
            os << "[";
            rhs.print_row(os, rhs.mat[0]);
            os << "]";
            return os;
        }
        
        int i = 0;
        os << "[";
        rhs.print_row(os, rhs.mat[i++]);
        os << endl;
        for (; i + 1 < rhs.rows; i++) {
            os << " ";
            rhs.print_row(os, rhs.mat[i]);
            os << endl;
        }
        os << " ";
        rhs.print_row(os, rhs.mat[i++]);
        os << "]";
        
        return os;
    }
    
    template <typename T>
    void matrix<T>::swap_row(int i, int j) {
        T* temp = mat[i];
        mat[i] = mat[j];
        mat[j] = temp;
    }
    
    template <typename T>
    template <typename type>
    void matrix<T>::divide_row(int row, type num) {
        for (int i = 0; i < cols; i++)
            mat[row][i] = mat[row][i] / num;
    }
    
    template <typename T>
    template <typename type>
    void matrix<T>::combine_row(int dst_row, int other_row, type factor) {
        for (int i = 0; i < cols; i++)
            mat[dst_row][i] = mat[dst_row][i] + mat[other_row][i] * factor;
    }
    
    template <typename T>
    void matrix<T>::clear() {
        if (!empty()) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
            
            rows = 0;
            cols = 0;
            mat = NULL;
        }
    }
    
    template <typename T>
    void matrix<T>::resize_row(T* row_arr, int i, int new_cols) const {
        if (cols < new_cols) {
            int j = 0;
            for (; j < cols; j++)
                row_arr[j] = mat[i][j];
            for (; j < new_cols; j++)
                row_arr[j] = T();
        } else {
            for (int j = 0; j < new_cols; j++)
                row_arr[j] = mat[i][j];
        }
    }
    
    template <typename T>
    void matrix<T>::print_row(T* row_arr) const {
        if (cols == 0) {
            cout << "it's an empty row" << endl;
            exit(1);
        }
        
        if (cols == 1) {
            cout << "[" << row_arr[0] << "]";
            return;
        }
        
        cout << "[";
        int i = 0;
        for (; i + 1 < cols; i++)
            cout << row_arr[i] << " ";
        cout << row_arr[i] << "]";
    }
    
    template <typename T>
    void matrix<T>::print_row(ostream& os, T* row_arr) const {
        if (cols == 0) {
            cout << "it's an empty row" << endl;
            exit(1);
        }
        
        if (cols == 1) {
            os << "[" << row_arr[0] << "]";
            return;
        }
        
        os << "[";
        int i = 0;
        for (; i + 1 < cols; i++)
            os << row_arr[i] << " ";
        os << row_arr[i] << "]";
    }
}


#endif /* cm_vect_mat_h */
