/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

enum class ComponentType: int
{
	Camera,
	Renderer
};

class ComponentTypeHelper
{
public:
	ComponentTypeHelper() = delete;
	
public:
	static std::string ComponentTypeToString(ComponentType data);
	static std::optional<ComponentType> StringToComponentType(const std::string& data);
	
};

