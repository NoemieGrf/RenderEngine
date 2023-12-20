/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "RendererPipelineType.h"
#include <unordered_map>
namespace Renderer
{
	
	std::string RendererPipelineTypeHelper::RendererPipelineTypeToString(RendererPipelineType data)
	{
		switch (data)
		{
			case RendererPipelineType::Forward: 
				return "Forward";
			case RendererPipelineType::Deferred: 
				return "Deferred";
			case RendererPipelineType::ForwardPlus: 
				return "ForwardPlus";
			default: 
				return "Unknown";
		}
		
	}
	
	std::optional<RendererPipelineType> RendererPipelineTypeHelper::StringToRendererPipelineType(const std::string& data)
	{
		static std::unordered_map<std::string, RendererPipelineType> map = 
		{
			{ "Forward", RendererPipelineType::Forward },
			{ "Deferred", RendererPipelineType::Deferred },
			{ "ForwardPlus", RendererPipelineType::ForwardPlus },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
}
