global.RND = function() { return "__META_" + Math.random().toString(36).substring(7); };

function genMetaFunction(_code)
{	
    var _return = ";return NectarCore::Global::undefined;}";
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
                _getVar += `var ${_match[2][i]}; if(__Nectar_VARLENGTH > ${i}) ${_match[2][i]} = __Nectar_VARARGS[${i}];`;
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
                        if(_code.indexOf("\"SCOPED_FUNCTION\";") > -1) 
						{
							_code = _code.replace(/"SCOPED_FUNCTION";/g, "                 ");
							_catch = "&";
						}

                        var _formated = "NectarCore::Type::function_t* " + _genFN +" = new NectarCore::Type::function_t([" + _catch + "](var __Nectar_THIS, NectarCore::VAR* __Nectar_VARARGS, int __Nectar_VARLENGTH) -> NectarCore::VAR" + _fn + _return + ");";
                        _formated += "var " + _match[1] + "=NectarCore::VAR(NectarCore::Enum::Type::Function, " + _genFN + ");";                        

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