//
//  cm_gj_elimination.h
//  opencv
//
//  Created by pengsida on 2017/10/10.
//  Copyright © 2017年 pengsida. All rights reserved.
//

#ifndef cm_gj_elimination_h
#define cm_gj_elimination_h

#include <cmath>
#include "cm_vec_mat.h"
#include "cm_manipulation.h"

namespace cm {
    class gj_elimin {
    private:
        vector<int> have_done;
        
    public:
        matrix<double> operator()(const matrix<double>& mat) {
            matrix<double> new_mat;
            operator()(mat, new_mat);
            
            return new_mat;
        }
        
        void operator()(const matrix<double>& mat, matrix<double>& new_mat) {
            int dim = mat.nrows();
            if (dim != mat.ncols()) {
                cout << "The input parameter is unexpected" << endl;
                exit(1);
            }
            
            matrix<double>::diag(dim, 1, new_mat);
            matrix<double> cal_mat(mat);
            have_done.assign(dim, 0);
            
            int max_row = -1;
            int max_col = -1;
            for (int i = 0; i < dim; i++) {
                find_max(cal_mat, max_row, max_col, dim);
                
                double max_num = cal_mat[max_row][max_col];
                if (is_zero(max_num)) {
                    cout << "The matrix is a singular matrix" << endl;
                    exit(1);
                }
                
                // 如果pivot不在对角线上，则将该行与对角线那一行交换
                if (max_row != max_col) {
                    cal_mat.swap_row(max_row, max_col);
                    new_mat.swap_row(max_row, max_col);
                }
                
                // 处理第max_col行，也就是现在pivot所处的这一行
                cal_mat.divide_row(max_col, max_num);
                new_mat.divide_row(max_col, max_num);
                cal_mat[max_col][max_col] = 1.0;
                
                // 处理第max_col列，使得该列的元素通过行之间的线形组合变为0
                deal_mat(cal_mat, new_mat, max_col, dim);
                
                // 记录已经处理过的行和列
                have_done[max_col] = 1;
//                cout << new_mat << endl;
            }
        }
        
    private:
        void find_max(const matrix<double>& cal_mat, int& max_row, int& max_col, int dim) {
            double max_num = 0;
            
            for (int i = 0; i < dim; i++) {
                // 如果该行已经处理过，则跳过
                if (have_done[i])
                    continue;
                for (int j = 0; j < dim; j++) {
                    // 如果该列已经处理过，则跳过
                    if (have_done[j])
                        continue;
                    // 如果该元素小等于最大值，则跳过
                    if (max_num >= fabs(cal_mat[i][j]))
                        continue;
                    max_num = fabs(cal_mat[i][j]);
                    max_row = i;
                    max_col = j;
                }
            }
        }
        
        // 将第1到第n行与第max_col行线性组合，使得第1到第n行的第max_col列元素为0
        template <typename T>
        inline void deal_mat(matrix<T>& mat, matrix<T>& con_mat, int max_col, int dim) {
            for (int i = 0; i < dim; i++) {
                // 如果是max_col这一行，则不处理
                if (i == max_col)
                    continue;
                __deal_mat(mat, con_mat, max_col, i);
                for (int j = 0; j < dim; j++) {
                    if (is_zero(con_mat[i][j]))
                        con_mat[i][j] = 0;
                }
            }
        }
        
        // 通过第i行与第j行的线形组合，使得mat的第j行第i列的元素为0
        template <typename T>
        inline void __deal_mat(matrix<T>& mat, matrix<T>& con_mat, int i, int j) const {
            T factor = mat[j][i];
            if (factor == 0)
                return;
            mat.combine_row(j, i, -factor);
            con_mat.combine_row(j, i, -factor);
        }
    };
}


#endif /* cm_gj_elimination_h */
