//
//  cm_manipulation.cpp
//  opencv
//
//  Created by pengsida on 2017/10/7.
//  Copyright © 2017年 pengsida. All rights reserved.
//

#include "cm_manipulation.h"
#include <cmath>

namespace cm {
    bool is_zero(double num) {
        return fabs(num) < 0.000000000001;
    }
}
