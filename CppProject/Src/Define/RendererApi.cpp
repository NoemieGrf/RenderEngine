/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "RendererApi.h"
#include <unordered_map>

std::string RendererApiHelper::RendererApiToString(RendererApi data)
{
	switch (data)
	{
		case RendererApi::OpenGL: 
			return "OpenGL";
		case RendererApi::Vulkan: 
			return "Vulkan";
		case RendererApi::D3D11: 
			return "D3D11";
		case RendererApi::D3D12: 
			return "D3D12";
		default: 
			return "Unknown";
	}
	
}

std::optional<RendererApi> RendererApiHelper::StringToRendererApi(const std::string& data)
{
	static std::unordered_map<std::string, RendererApi> map = 
	{
		{ "OpenGL", RendererApi::OpenGL },
		{ "Vulkan", RendererApi::Vulkan },
		{ "D3D11", RendererApi::D3D11 },
		{ "D3D12", RendererApi::D3D12 },
	};
	
	if (map.contains(data))
		return map[data];
	
	return std::nullopt;
}

