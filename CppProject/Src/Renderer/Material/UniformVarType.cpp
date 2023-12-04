/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "UniformVarType.h"
#include <unordered_map>
namespace Renderer
{
	
	std::string UniformVarTypeHelper::UniformVarTypeToString(UniformVarType data)
	{
		switch (data)
		{
			case UniformVarType::Int: 
				return "Int";
			case UniformVarType::Float: 
				return "Float";
			case UniformVarType::Mat3: 
				return "Mat3";
			case UniformVarType::Mat4: 
				return "Mat4";
			case UniformVarType::Texture2D: 
				return "Texture2D";
			default: 
				return {};
		}
		
	}
	
	UniformVarType UniformVarTypeHelper::StringToUniformVarType(const std::string& data)
	{
		static std::unordered_map<std::string, UniformVarType> map = 
		{
			{ "Int", UniformVarType::Int },
			{ "Float", UniformVarType::Float },
			{ "Mat3", UniformVarType::Mat3 },
			{ "Mat4", UniformVarType::Mat4 },
			{ "Texture2D", UniformVarType::Texture2D },
		};
		
		if (map.contains(data))
			return map[data];
		
		return UniformVarType::Int;
	}
	
}
