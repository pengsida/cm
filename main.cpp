//
//  main.cpp
//  opencv
//
//  Created by pengsida on 2017/10/6.
//  Copyright © 2017年 pengsida. All rights reserved.
//

#include <iostream>
#include "cm_vec_mat.h"
#include "cm_mat_inv.h"
#include "cm_gj_elimination.h"
#include "cm_lu_doc.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cm;

//int main() {
//    cm::vector<double> test({1, 2, 3});
//    cout << test + cm::vector<double>({5, 6, 10}) << endl;
//    cm::matrix<double> other({{1, 3, 1}, {2, 1, 1}, {2, 2, 1}});
//    typedef typename matrix<double>::value_type value_type;
//    cout << other << endl;
//    cout << lu_doc()(other) << endl;
//    return 0;
//}

int main() {
    string line;
    ifstream my_file("/Users/pengsida/Downloads/orl_faces/s1/1.pgm");
    int count = 0;
    int times = 0;
    cm::matrix<double> test(92, 92);
    
    if (my_file.is_open()) {
        getline(my_file, line);
        getline(my_file, line);
        getline(my_file, line);
        getline(my_file, line);
        for (int i = 0; i < 92; i++) {
            for (int j = 0; j < 92; j++) {
                count = (unsigned char)line[i*92+j];
                test[i][j] = (double)count;
            }
        }
    }
    
    cm::matrix<double> ttest;
    cm::matrix<double>::transpose(test, ttest);
    cout << gj_elimin()(ttest)*ttest << endl;
}
