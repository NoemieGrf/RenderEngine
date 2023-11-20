from typing import Dict, List


class EnumConfig:
    def __init__(self, enum_config_json: Dict):
        self.enum_name: str = enum_config_json['EnumName']
        self.enum_type: str = enum_config_json['Type']
        self.value_array: List = enum_config_json['Value']
