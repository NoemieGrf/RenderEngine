/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer
{
	enum class ShaderType: int
	{
		Vertex,
		Pixel,
		Count
	};
	
	class ShaderTypeHelper
	{
	public:
		ShaderTypeHelper() = delete;
		
	public:
		static std::optional<std::string> ShaderTypeToString(ShaderType data);
		static std::optional<ShaderType> StringToShaderType(const std::string& data);
		
	};

}
