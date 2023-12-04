/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>

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
		static std::string UniformVarTypeToString(UniformVarType data);
		static UniformVarType StringToUniformVarType(const std::string& data);
		
	};

}
