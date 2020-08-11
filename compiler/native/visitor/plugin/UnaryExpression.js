/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
 
function UnaryExpression(_path) 
{ 
	if (_path.node.operator == "typeof")
	{
		if(_path.node.argument.type == "Identifier")	
		{
			_path.replaceWithSourceString("__NJS_Typeof(" + _path.node.argument.name + ")");
		}
		else if(_path.node.argument.extra)
		{
			_path.replaceWithSourceString("__NJS_Typeof(" + _path.node.argument.extra.raw + ")");
		}
		else if (_path.node.argument.type == "MemberExpression")
		{
			_path.replaceWithSourceString("__NJS_Typeof(" + VISITOR.memberExpression(_path.node.argument) + ")");
		}
		else if (_path.node.argument.type == "CallExpression")
		{
			_path.replaceWithSourceString("__NJS_Typeof(" + VISITOR.callExpression(_path.node.argument) + ")");
		}
		_path.skip();
	}
}
module.exports = UnaryExpression;