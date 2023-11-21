/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once
#include <string>
namespace Renderer
{
	enum class ShaderDataType: int
	{
		None,
		Bool,
		Float,
		Float2,
		Float3,
		Float4,
		Matrix3x3,
		Matrix4x4,
		Int,
		Int2,
		Int3,
		Int4
	};
	
	class ShaderDataTypeHelper
	{
	public:
		ShaderDataTypeHelper() = delete;
		
	public:
		static std::string ShaderDataTypeToString(ShaderDataType data);
		static ShaderDataType StringToShaderDataType(const std::string& data);
		static unsigned int GetShaderDataTypeSize(ShaderDataType data);
		static unsigned int GetShaderDataCount(ShaderDataType data);
		
	};

}
