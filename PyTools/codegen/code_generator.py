from .enum_gen_config import EnumConfig


class CodeGenerator:
    content: str
    indent: int

    def __init__(self) -> None:
        self.content = ''
        self.indent = 0

    def append(self, s: str) -> None:
        self.content += s

    def new_line(self) -> None:
        self.content += '\n'
        for i in range(self.indent):
            self.content += '\t'

    def new_line_with_indent_increase(self) -> None:
        self.indent_increase()
        self.new_line()

    def new_line_with_indent_decrease(self) -> None:
        self.indent_decrease()
        self.new_line()

    def indent_increase(self) -> None:
        self.indent += 1

    def indent_decrease(self) -> None:
        self.indent -= 1

    def write_to_file(self, path: str) -> None:
        f = open(path, 'w', encoding='utf-8')
        f.write(self.content)
        f.close()


def gen_header_comment(cg: CodeGenerator) -> None:
    cg.append('/* ****************************** \n')
    cg.append(' * Auto Generated File ! \n')
    cg.append(' * ******************************/\n')
    cg.new_line()


def gen_pragma_once(cg: CodeGenerator) -> None:
    cg.append('#pragma once')
    cg.new_line()


def gen_namespace_begin(cg: CodeGenerator, namespace_name: str) -> None:
    cg.new_line()
    cg.append('namespace ' + namespace_name)
    cg.new_line()
    cg.append('{')
    cg.new_line_with_indent_increase()


def gen_namespace_end(cg: CodeGenerator) -> None:
    cg.new_line_with_indent_decrease()
    cg.append('{')


def gen_enum_class(cg: CodeGenerator, enum_config: EnumConfig) -> None:
    cg.append('enum class ' + enum_config.enum_name + ': ' + enum_config.enum_type)
    cg.new_line()
    cg.append('{')
    cg.new_line_with_indent_increase()

    size: int = len(enum_config.value_array)
    index: int = 0
    for enum_value in enum_config.value_array:
        cg.append(enum_value)
        index += 1
        if index < size:
            cg.append(',')
            cg.new_line()

    cg.new_line_with_indent_decrease()
    cg.append('};')

    pass
