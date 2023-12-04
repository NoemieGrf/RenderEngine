import json
from codegen.enum_gen_config import EnumConfig
from codegen.function_gen_config import FunctionConfig
from codegen.code_generator import CodeGenerator


class CustomEnumConverterConfig:
    def __init__(self, name: str, return_type: str, return_default: str, mapping: list[dict[str, str]]) -> None:
        self.name: str = name
        self.return_type: str = return_type
        self.return_default: str = return_default
        self.mapping: list[dict[str, str]] = mapping

    def get_function(self, enum_name: str, class_name: str) -> FunctionConfig:
        f: FunctionConfig = FunctionConfig(
            self.name,
            self.return_type,
            {enum_name: 'data'},
            class_name
        )
        f.add_static()
        return f


class Processor:
    def __init__(self, single_enum_config: dict):
        self.enum_config: EnumConfig = EnumConfig(single_enum_config)

        if 'Namespace' in single_enum_config.keys():
            self.namespace: str | None = single_enum_config['Namespace']
        else:
            self.namespace: str | None = None

        self.has_string_converter: bool = single_enum_config['StringConverter']
        self.helper_class_name: str = self.enum_config.enum_name + 'Helper'

        if self.has_string_converter:
            enum_to_string_func_name: str = self.enum_config.enum_name + 'ToString'
            enum_to_string_input: dict[str, str] = {self.enum_config.enum_name: 'data'}

            self.enum_to_string_function_config = FunctionConfig(
                enum_to_string_func_name,
                'std::optional<std::string>',
                enum_to_string_input,
                self.helper_class_name
            )
            self.enum_to_string_function_config.add_static()

            string_to_enum_func_name: str = 'StringTo' + self.enum_config.enum_name
            string_to_enum_input: dict[str, str] = {'const std::string&': 'data'}

            self.string_to_enum_function_config = FunctionConfig(
                string_to_enum_func_name,
                'std::optional<{}>'.format(self.enum_config.enum_name),
                string_to_enum_input,
                self.helper_class_name
            )
            self.string_to_enum_function_config.add_static()

        if 'CustomConverter' not in single_enum_config.keys():
            self.custom_converter: list[CustomEnumConverterConfig] | None = None
        else:
            self.custom_converter: list[CustomEnumConverterConfig] | None = []
            for single_custom_converter_config in single_enum_config['CustomConverter']:
                self.custom_converter.append(CustomEnumConverterConfig(
                    single_custom_converter_config['Name'],
                    single_custom_converter_config['ReturnValue'],
                    single_custom_converter_config['DefaultReturn'],
                    single_custom_converter_config['Map']
                ))

        file_name: str = single_enum_config['EnumName']
        file_base_path: str = single_enum_config['FilePath']
        self.header_file_path: str = file_base_path + file_name + '.h'
        self.cpp_file_path: str = file_base_path + file_name + '.cpp'

    def generator_header_file(self) -> None:
        cg: CodeGenerator = CodeGenerator()

        # auto gen comment
        cg.gen_header_comment().new_line()

        # header pragma once
        cg.gen_pragma_once().new_line().new_line()

        # include string
        cg.gen_include('<string>').new_line()
        cg.gen_include('<optional>').new_line()
        cg.new_line()

        # namespace begin
        if self.namespace is not None:
            cg.gen_namespace(self.namespace).new_line().left_bracket()
            cg.indent_increase().new_line()

        # enum class
        cg.gen_enum_class(self.enum_config)

        # converter function declaration
        cg.new_line()
        self.generator_helper_class(cg)

        # namespace end
        if self.namespace is not None:
            cg.indent_decrease().new_line().right_bracket()

        cg.new_line()
        cg.write_to_file(self.header_file_path)
        pass

    def generator_helper_class(self, cg: CodeGenerator) -> None:
        if not self.has_string_converter and self.custom_converter is None:
            return

        cg.new_line()

        # class begin
        cg.append('class ').append(self.helper_class_name).new_line()
        cg.left_bracket().new_line()

        # public begin
        cg.append('public:').indent_increase().new_line()

        # deleted constructor
        cctor: FunctionConfig = FunctionConfig(self.helper_class_name, None, {}, self.helper_class_name)
        cg.gen_function(cctor, True)
        cg.append(' = delete;').new_line()

        # public end
        cg.indent_decrease().new_line()

        # public begin
        cg.append('public:').indent_increase().new_line()

        # converter method declarations
        self.generator_string_converter_declaration(cg)
        self.generator_custom_converter_declaration(cg)

        # public end
        cg.indent_decrease().new_line()

        # class end
        cg.right_bracket().semicolon().indent_decrease().new_line()

        pass

    def generator_string_converter_declaration(self, cg: CodeGenerator) -> None:
        if not self.has_string_converter:
            return

        cg.gen_function(self.enum_to_string_function_config, True).semicolon()
        cg.new_line()
        cg.gen_function(self.string_to_enum_function_config, True).semicolon()
        cg.new_line()
        pass

    def generator_custom_converter_declaration(self, cg: CodeGenerator) -> None:
        if self.custom_converter is None:
            return

        for custom_converter_config in self.custom_converter:
            cg.gen_function(custom_converter_config.get_function(self.enum_config.enum_name, self.helper_class_name),
                            True).semicolon()
            cg.new_line()
        pass

    def generate_cpp_file(self) -> None:
        if not self.has_string_converter and self.custom_converter is None:
            return

        cg: CodeGenerator = CodeGenerator()

        # auto gen comment
        cg.gen_header_comment().new_line()

        # include header
        cg.gen_include('\"' + self.enum_config.enum_name + '.h\"').new_line()
        cg.gen_include('<unordered_map>').new_line()

        # namespace begin
        if self.namespace is not None:
            cg.gen_namespace(self.namespace).new_line().left_bracket()
            cg.indent_increase().new_line()

        if self.has_string_converter:
            self.generator_enum_to_string_converter_implement(cg)
            self.generator_string_to_enum_converter_implement(cg)

        if self.custom_converter is not None:
            self.generator_custom_converter_implement(cg)

        # namespace end
        if self.namespace is not None:
            cg.indent_decrease().new_line().right_bracket()

        cg.new_line()
        cg.write_to_file(self.cpp_file_path)
        pass

    def generator_enum_to_string_converter_implement(self, cg: CodeGenerator) -> None:
        # enum to string
        cg.new_line()
        cg.gen_function(self.enum_to_string_function_config, False).new_line()
        cg.left_bracket().indent_increase().new_line()

        cg.append('switch (data)').new_line()
        cg.left_bracket().indent_increase().new_line()

        for enum_value in self.enum_config.value_array:
            if enum_value == 'Count':
                continue
            cg.append('case ' + self.enum_config.enum_name + '::' + enum_value + ': ').indent_increase().new_line()
            cg.append('return \"' + enum_value + '\"').semicolon().indent_decrease().new_line()

        cg.append('default: ').indent_increase().new_line()
        cg.append('return std::nullopt').semicolon().indent_decrease()

        cg.indent_decrease().new_line()
        cg.right_bracket().new_line()

        cg.indent_decrease().new_line()
        cg.right_bracket().new_line()
        pass

    def generator_string_to_enum_converter_implement(self, cg: CodeGenerator) -> None:
        # string to enum
        cg.new_line()
        cg.gen_function(self.string_to_enum_function_config, False).new_line()
        cg.left_bracket().indent_increase().new_line()

        cg.append('static std::unordered_map<std::string, ' + self.enum_config.enum_name + '> map = ').new_line()
        cg.left_bracket().indent_increase()

        for enum_value in self.enum_config.value_array:
            if enum_value == 'Count':
                continue
            cg.new_line()
            cg.left_bracket().append(' \"' + enum_value + '\", ' + self.enum_config.enum_name + '::' + enum_value + ' ')
            cg.right_bracket().append(',')

        cg.indent_decrease().new_line().right_bracket().semicolon().new_line()

        cg.new_line()
        cg.append('if (map.contains(data))').indent_increase().new_line()
        cg.append('return map[data];').indent_decrease().new_line()

        cg.new_line()
        cg.append('return std::nullopt').semicolon()

        cg.indent_decrease().new_line()
        cg.right_bracket().new_line()
        pass

    def generator_custom_converter_implement(self, cg: CodeGenerator) -> None:
        for custom_converter_config in self.custom_converter:
            function_config = custom_converter_config.get_function(self.enum_config.enum_name, self.helper_class_name)
            cg.new_line()
            cg.gen_function(function_config, False).new_line()
            cg.left_bracket().indent_increase().new_line()

            cg.append('static std::unordered_map<' + self.enum_config.enum_name + ', ')
            cg.append(custom_converter_config.return_type + '> map = ').new_line()
            cg.left_bracket().indent_increase()

            for single_map in custom_converter_config.mapping:
                for map_key, map_value in single_map.items():
                    cg.new_line()
                    cg.left_bracket().append(self.enum_config.enum_name + '::' + map_key + ', ' + map_value + ' ')
                    cg.right_bracket().append(',')

            cg.indent_decrease().new_line().right_bracket().semicolon().new_line()

            cg.new_line()
            cg.append('if (map.contains(data))').indent_increase().new_line()
            cg.append('return map[data];').indent_decrease().new_line()

            cg.new_line()
            cg.append('return ' + custom_converter_config.return_default).semicolon()

            cg.indent_decrease().new_line()
            cg.right_bracket().new_line()
            cg.new_line()
        pass


def main() -> None:
    config_file: str = 'enum_config.json'
    with open(config_file, 'r', encoding='utf-8') as fp:
        enum_config_array = json.load(fp)['EnumGenConfig']
        for single_enum_config in enum_config_array:
            processor: Processor = Processor(single_enum_config)
            processor.generator_header_file()
            processor.generate_cpp_file()
    pass


if __name__ == '__main__':
    main()
