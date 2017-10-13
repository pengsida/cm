//
//  cm_mat_inv.h
//  opencv
//
//  Created by pengsida on 2017/10/9.
//  Copyright © 2017年 pengsida. All rights reserved.
//

#ifndef cm_mat_inv_h
#define cm_mat_inv_h

#include "cm_vec_mat.h"

namespace cm{
    class mat_inv {
    public:
        matrix<double> operator()(const matrix<double>& mat) const {
            matrix<double> new_mat;
            operator()(mat, new_mat);
            return new_mat;
        }
        
        void operator()(const matrix<double>& mat, matrix<double>& new_mat) const {
            if (mat.nrows() != mat.ncols()) {
                cout << "The input parameter is unexpected" << endl;
                exit(1);
            }
            
            int dim = mat.nrows();
            matrix<double>::diag(dim, 1, new_mat);
            matrix<double> cal_mat(mat);
            
            for (int i = 0; i < dim; i++) {
                int max = find_max(cal_mat, i, dim);
                
                // 交换最大的行
                cal_mat.swap_row(i, max);
                new_mat.swap_row(i, max);
                
                // 除以第i行第i列的元素
                double max_num = cal_mat[i][i];
                if (max_num == 0) {
                    cout << "The input parameter is unexpected" << endl;
                    exit(1);
                }
                cal_mat.divide_row(i, max_num);
                new_mat.divide_row(i, max_num);
                
                // 将第i+1到第n行与第i行线性组合，使得第i+1到第n行的第i列元素为0
                deal_mat(cal_mat, new_mat, i, dim);
            }
            
            // 将cal_mat的上三角除了对角线的元素，通过线性组合都变为0
            for (int i = dim - 1; i >= 0; i--)
                deal_mat_rev(cal_mat, new_mat, i);
        }
        
    private:
        // 找到从第i到第n行中第j行第i列最大的那一行
        template <typename T>
        int find_max(const matrix<T>& mat, int i, int dim) const {
            int max = i;
            
            for (int j = i + 1; j < dim; j++) {
                if (mat[j][i] < mat[max][i])
                    max = j;
            }
            
            return max;
        }
        
        // 将第i+1到第n行与第i行线性组合，使得第i+1到第n行的第i列元素为0
        template <typename T>
        inline void deal_mat(matrix<T>& mat, matrix<T>& con_mat, int i, int dim) const {
            for (int j = i + 1; j < dim; j++)
                __deal_mat(mat, con_mat, i, j);
        }
        
        // 将第i+1到第n行与第i行线性组合，使得第i-1到第0行的第i列元素为0
        template <typename T>
        inline void deal_mat_rev(matrix<T>& mat, matrix<T>& con_mat, int i) const {
            for (int j = i - 1; j >= 0; j--)
                __deal_mat(mat, con_mat, i, j);
        }
        
        // 通过第i行与第j行的线形组合，使得mat的第j行第i列的元素为0
        template <typename T>
        inline void __deal_mat(matrix<T>& mat, matrix<T>& con_mat, int i, int j) const {
            T factor = mat[j][i] / mat[i][i];
            if (factor == 0)
                return;
            mat.combine_row(j, i, -factor);
            con_mat.combine_row(j, i, -factor);
        }
    };
}

#endif /* cm_mat_inv_h */
