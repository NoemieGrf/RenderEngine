/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once
#include <string>
enum class RendererApi: int
{
	OpenGL,
	Vulkan,
	D3D11,
	D3D12
};

class RendererApiHelper
{
public:
	RendererApiHelper() = delete;
	
public:
	static std::string RendererApiToString(RendererApi data);
	static RendererApi StringToRendererApi(const std::string& data);
	
};

