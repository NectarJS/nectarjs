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
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <vector>
 #include <memory>

 using namespace std;

 #include "njs.h"
 using namespace NJS;
 using namespace NJS::Value;
 
 var __NJS_ENV = "std";
 var __NJS_PLATFORM = "{{__PLATFORM__}}";
 
/*** $ERROR ***/
NJS::VAR __NJS_DOLLAR_ERROR = __NJS_Create_Var_Unscoped_Anon( __NJS_Log_Console(__NJS_VARARGS[0]); exit(1); return NJS::VAR(); );
/* end $ERROR */
 
 {INCLUDE}
 
 {DECL}

int main(int argc, char* argv[])
{
	var __NJS_ARGS = __NJS_Create_Array();
	for( int i = 0; i < argc; i++)
	{
		__NJS_Object_Set(i, NJS::VAR(argv[i]), __NJS_ARGS);
	}
	
	{INIT}

	{CODE}
	return 0;
}
