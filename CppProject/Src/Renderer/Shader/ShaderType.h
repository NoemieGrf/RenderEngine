/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>

namespace Renderer
{
	enum class ShaderType: int
	{
		VertexShader,
		PixelShader
	};
	
	class ShaderTypeHelper
	{
	public:
		ShaderTypeHelper() = delete;
		
	public:
		static std::string ShaderTypeToString(ShaderType data);
		static ShaderType StringToShaderType(const std::string& data);
		
	};

}
