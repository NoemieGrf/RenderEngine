/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer
{
	enum class UniformVariableType: int
	{
		Int,
		Uint,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Texture2D
	};
	
	class UniformVariableTypeHelper
	{
	public:
		UniformVariableTypeHelper() = delete;
		
	public:
		static std::string UniformVariableTypeToString(UniformVariableType data);
		static std::optional<UniformVariableType> StringToUniformVariableType(const std::string& data);
		
	};

}
