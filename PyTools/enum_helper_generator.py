import json
import codegen.code_generator
from codegen.enum_gen_config import EnumConfig
from codegen.code_generator import CodeGenerator
from typing import Dict, List


class Processor:
    def __init__(self, single_enum_config: Dict):
        self.enum_config: EnumConfig = EnumConfig(single_enum_config)

        if 'Namespace' in single_enum_config.keys():
            self.namespace: str | None = single_enum_config['Namespace']
        else:
            self.namespace: str | None = None

        file_name: str = single_enum_config['EnumName']
        file_base_path: str = single_enum_config['FilePath']
        self.header_file_path: str = file_base_path + file_name + '.h'
        self.cpp_file_path: str = file_base_path + file_name + '.cpp'

    def generator_header_file(self) -> None:
        cg: CodeGenerator = CodeGenerator()

        codegen.code_generator.gen_header_comment(cg)

        if self.namespace is not None:
            codegen.code_generator.gen_namespace_begin(cg, self.namespace)

        cg.new_line()
        codegen.code_generator.gen_enum_class(cg, self.enum_config)
        cg.new_line()

        if self.namespace is not None:
            codegen.code_generator.gen_namespace_end(cg)

        cg.write_to_file(self.header_file_path)
        pass

    def generate_cpp_file(self) -> None:

        pass


def main() -> None:
    config_file: str = 'enum_config.json'
    with open(config_file, 'r', encoding='utf8') as fp:
        enum_config_array = json.load(fp)['EnumGenConfig']
        for single_enum_config in enum_config_array:
            processor: Processor = Processor(single_enum_config)
            processor.generator_header_file()
            processor.generate_cpp_file()
    pass


if __name__ == '__main__':
    main()
