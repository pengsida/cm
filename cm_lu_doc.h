//
//  cm_lu_doc.h
//  opencv
//
//  Created by pengsida on 2017/10/11.
//  Copyright © 2017年 pengsida. All rights reserved.
//

#ifndef cm_lu_doc_h
#define cm_lu_doc_h

#include "cm_vec_mat.h"

namespace cm {
    class lu_doc {
    public:
        matrix<double> operator()(const matrix<double>& mat) {
            matrix<double> new_mat;
            
            operator()(mat, new_mat);
            return new_mat;
        }
        
        void operator()(const matrix<double>& mat, matrix<double>& new_mat) {
            int dim = mat.nrows();
            if (dim != mat.ncols())
                throw "The input parameter is unexpected";
            
            new_mat.assign(dim, dim, 0);
            
            for (int j = 0; j < dim; j++) {
                int i = 0;
                // 处理u矩阵从第0行到第j行的第j列元素
                for (; i <= j; i++)
                    new_mat[i][j] = mat[i][j] - dot_vec(new_mat, new_mat, i, j);
                // 处理l矩阵从第j+1行到第n-1行的第j列元素
                for (; i < dim; i++)
                    new_mat[i][j] = (mat[i][j] - dot_vec(new_mat, new_mat, i, j)) / new_mat[j][j];
            }
        }
        
    private:
        double dot_vec(const matrix<double>& l_mat, const matrix<double>& u_mat, int row, int col) {
            double sum = 0;
            for (int k = 0; k < col; k++) {
                if (row == k)
                    sum = sum + u_mat[k][col];
                else
                    sum = sum + l_mat[row][k] * u_mat[k][col];
            }
            return sum;
        }
    };
}


#endif /* cm_lu_doc_h */
