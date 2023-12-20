/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer
{
	enum class RendererPipelineType: int
	{
		Forward,
		Deferred,
		ForwardPlus
	};
	
	class RendererPipelineTypeHelper
	{
	public:
		RendererPipelineTypeHelper() = delete;
		
	public:
		static std::string RendererPipelineTypeToString(RendererPipelineType data);
		static std::optional<RendererPipelineType> StringToRendererPipelineType(const std::string& data);
		
	};

}
