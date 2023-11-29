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
			case ShaderType::VertexShader: 
				return "VertexShader";
			case ShaderType::PixelShader: 
				return "PixelShader";
			
		}
		
	}
	
	ShaderType ShaderTypeHelper::StringToShaderType(const std::string& data)
	{
		static std::unordered_map<std::string, ShaderType> map = 
		{
			{ "VertexShader", ShaderType::VertexShader },
			{ "PixelShader", ShaderType::PixelShader },
		};
		
		if (map.contains(data))
			return map[data];
		
		return ShaderType::VertexShader;
	}
	
}
