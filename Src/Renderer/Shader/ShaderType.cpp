/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "ShaderType.h"
#include <unordered_map>
namespace Renderer
{
	
	std::string ShaderTypeHelper::ShaderTypeToString(ShaderType data)
	{
		switch (data)
		{
			case ShaderType::Vertex: 
				return "Vertex";
			case ShaderType::Pixel: 
				return "Pixel";
			default: 
				return "Unknown";
		}
		
	}
	
	std::optional<ShaderType> ShaderTypeHelper::StringToShaderType(const std::string& data)
	{
		static std::unordered_map<std::string, ShaderType> map = 
		{
			{ "Vertex", ShaderType::Vertex },
			{ "Pixel", ShaderType::Pixel },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
}
