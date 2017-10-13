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

using namespace std;
using namespace cm;

int main() {
    cm::vector<double> test({1, 2, 3});
    cout << test + cm::vector<double>({5, 6, 10}) << endl;
    cm::matrix<double> other({{1, 3, 1}, {2, 1, 1}, {2, 2, 1}});
    typedef typename matrix<double>::value_type value_type;
    cout << other << endl;
    cout << lu_doc()(other) << endl;
    return 0;
}
