function hoistingFunction(_code)
{	
	var _hoisting = "";
	var _searchFN = new RegExp(/function +(.[a-zA-Z0-9_\-]*) *\((.*)\)/);
	var _index = _code.search(_searchFN);
	while(_index > -1)
	{
		var _count = 0;
		var _start = -1;
		var _end = -1;
		let _match = _searchFN.exec(_code);

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
						_hoisting += _code.substring(_index, _end + 1) + "\n";
						_code = _code.slice(0, _index) + _code.slice(_end + 1);
						break;
					}
				}
		}
		_index = _code.search(_searchFN);
	}
	
	return _hoisting + _code;
}
module.exports = hoistingFunction;