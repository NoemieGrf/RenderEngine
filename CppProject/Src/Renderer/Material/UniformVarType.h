/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer
{
	enum class UniformVarType: int
	{
		Int,
		Float,
		Mat3,
		Mat4,
		Texture2D
	};
	
	class UniformVarTypeHelper
	{
	public:
		UniformVarTypeHelper() = delete;
		
	public:
		static std::optional<std::string> UniformVarTypeToString(UniformVarType data);
		static std::optional<UniformVarType> StringToUniformVarType(const std::string& data);
		
	};

}
