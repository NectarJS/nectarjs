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

global.RND = function() { return "__META_" + Math.random().toString(36).substring(7); };

function genMetaFunction(_code)
{	
    var _return = ";return __NJS_Create_Undefined();}";
    var _searchFN = new RegExp(/function (.[a-zA-Z0-9_\-]*) *\((.*)\)/);
    var _index = _code.search(_searchFN);
    while(_index > -1)
    {
        var _genFN = "__NJS_FN_" + RND();
        var _count = 0;
        var _start = -1;
        var _end = -1;
    
        let _match = _searchFN.exec(_code);

        _match[2] = _match[2].split(",");
        var _getVar = "";
        for(var i = 0; i < _match[2].length; i++)
        {
            if(_match[2][i].length > 0)
            {
                _getVar += `var ${_match[2][i]}; if(__NJS_VARARGS.size() > ${i}) ${_match[2][i]} = __NJS_VARARGS[${i}];`;
            }
        }
        for(var i = _index; i < _code.length; i++)
        {
                if(_code[i] == "{")
                {
                        if(_start == -1) _start = i;
                        _count++;
                }
                else if(_code[i] == "}")
                {
                    
                    _end = i;
                    _count--;
                    if(_count == 0)
                    {
                        var _fn = "{" + _getVar + _code.substring(_start + 1, _end);
                        var _catch = "";
                        if(_code.indexOf("'SCOPED_FUNCTION';") > -1) 
						{
							_code = _code.replace(/'SCOPED_FUNCTION';/g, "                  ");
							_catch = "=";
						}

                        var _formated = "__NJS_DECL_FUNCTION<NJS::VAR (var, vector<var>)>* " + _genFN +" = new __NJS_DECL_FUNCTION<NJS::VAR (var, vector<var>)>([" + _catch + "](var __INJECTED_THIS, vector<var> __NJS_VARARGS ) -> NJS::VAR" + _fn + _return + ");";
                        _formated += "var " + _match[1] + "=NJS::VAR(NJS::Enum::Type::FUNCTION, " + _genFN + ");";                        

						_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');
                        break;
                    }
                }
        }
        _index = _code.search(_searchFN);
    }
    return _code;
}

module.exports = genMetaFunction;