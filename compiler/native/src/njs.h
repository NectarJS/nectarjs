/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <stdarg.h>
#include <tuple>
#include <bitset>

#ifdef __NJS_ENV_ARDUINO
#include <util/delay.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
#include <math.h>
#undef max
#undef min
#include <limits>
#else
#include <functional>
#include <cmath>
#include <limits>
#include <mutex>
#include <chrono>
#include <thread>
#endif

#include "enum.h"
#include "macro.h"

namespace NJS
{
	struct VAR;
	namespace Class
	{
		class Base;
		class Undefined;
		class Boolean;
		class String;
		class Array;
		class Object;
		class Function;
		class Native;
		class Struct;
		class FixedArray;
	}
} // namespace NJS

#include "var_header.h"
#include "type.h"
#include "classes_header.h"
#include "functions.h"
#include "native.h"
#include "values.h"
#include "this.h"
#include "class/number_header.h"
#include "var.h"
#include "objmgmt.h"
#include "event.h"
#include "classes.h"
#include "operator.h"

#include "std_global_js.h"
