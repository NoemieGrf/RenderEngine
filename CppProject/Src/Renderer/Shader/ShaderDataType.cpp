/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "ShaderDataType.h"
#include <unordered_map>
namespace Renderer
{
	
	std::optional<std::string> ShaderDataTypeHelper::ShaderDataTypeToString(ShaderDataType data)
	{
		switch (data)
		{
			case ShaderDataType::None: 
				return "None";
			case ShaderDataType::Bool: 
				return "Bool";
			case ShaderDataType::Float: 
				return "Float";
			case ShaderDataType::Float2: 
				return "Float2";
			case ShaderDataType::Float3: 
				return "Float3";
			case ShaderDataType::Float4: 
				return "Float4";
			case ShaderDataType::Matrix3x3: 
				return "Matrix3x3";
			case ShaderDataType::Matrix4x4: 
				return "Matrix4x4";
			case ShaderDataType::Int: 
				return "Int";
			case ShaderDataType::Int2: 
				return "Int2";
			case ShaderDataType::Int3: 
				return "Int3";
			case ShaderDataType::Int4: 
				return "Int4";
			default: 
				return std::nullopt;
		}
		
	}
	
	std::optional<ShaderDataType> ShaderDataTypeHelper::StringToShaderDataType(const std::string& data)
	{
		static std::unordered_map<std::string, ShaderDataType> map = 
		{
			{ "None", ShaderDataType::None },
			{ "Bool", ShaderDataType::Bool },
			{ "Float", ShaderDataType::Float },
			{ "Float2", ShaderDataType::Float2 },
			{ "Float3", ShaderDataType::Float3 },
			{ "Float4", ShaderDataType::Float4 },
			{ "Matrix3x3", ShaderDataType::Matrix3x3 },
			{ "Matrix4x4", ShaderDataType::Matrix4x4 },
			{ "Int", ShaderDataType::Int },
			{ "Int2", ShaderDataType::Int2 },
			{ "Int3", ShaderDataType::Int3 },
			{ "Int4", ShaderDataType::Int4 },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
	unsigned int ShaderDataTypeHelper::GetShaderDataTypeSize(ShaderDataType data)
	{
		static std::unordered_map<ShaderDataType, unsigned int> map = 
		{
			{ShaderDataType::None, 0 },
			{ShaderDataType::Bool, 1 },
			{ShaderDataType::Float, 4 },
			{ShaderDataType::Float2, 4 * 2 },
			{ShaderDataType::Float3, 4 * 3 },
			{ShaderDataType::Float4, 4 * 4 },
			{ShaderDataType::Matrix3x3, 4 * 3 * 3 },
			{ShaderDataType::Matrix4x4, 4 * 4 * 4 },
			{ShaderDataType::Int, 4 },
			{ShaderDataType::Int2, 4 * 2 },
			{ShaderDataType::Int3, 4 * 3 },
			{ShaderDataType::Int4, 4 * 4 },
		};
		
		if (map.contains(data))
			return map[data];
		
		return 0;
	}
	
	
	unsigned int ShaderDataTypeHelper::GetShaderDataCount(ShaderDataType data)
	{
		static std::unordered_map<ShaderDataType, unsigned int> map = 
		{
			{ShaderDataType::None, 0 },
			{ShaderDataType::Bool, 1 },
			{ShaderDataType::Float, 1 },
			{ShaderDataType::Float2, 2 },
			{ShaderDataType::Float3, 3 },
			{ShaderDataType::Float4, 4 },
			{ShaderDataType::Matrix3x3, 3 * 3 },
			{ShaderDataType::Matrix4x4, 4 * 4 },
			{ShaderDataType::Int, 1 },
			{ShaderDataType::Int2, 2 },
			{ShaderDataType::Int3, 3 },
			{ShaderDataType::Int4, 4 },
		};
		
		if (map.contains(data))
			return map[data];
		
		return 0;
	}
	
	
}
