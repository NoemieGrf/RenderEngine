/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "ComponentType.h"
#include <unordered_map>

std::string ComponentTypeHelper::ComponentTypeToString(ComponentType data)
{
	switch (data)
	{
		case ComponentType::Camera: 
			return "Camera";
		case ComponentType::Light: 
			return "Light";
		case ComponentType::Renderer: 
			return "Renderer";
		default: 
			return "Unknown";
	}
	
}

std::optional<ComponentType> ComponentTypeHelper::StringToComponentType(const std::string& data)
{
	static std::unordered_map<std::string, ComponentType> map = 
	{
		{ "Camera", ComponentType::Camera },
		{ "Light", ComponentType::Light },
		{ "Renderer", ComponentType::Renderer },
	};
	
	if (map.contains(data))
		return map[data];
	
	return std::nullopt;
}

