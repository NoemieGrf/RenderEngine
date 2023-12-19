import subprocess
import os
from . import tool_path


def compile_glsl(glsl_path: str) -> None:
    print('glslc compile {}'.format(glsl_path))
    spv_path: str = glsl_path.replace('/Shader/', '/ShaderBin/SpirV/') + '.spv'

    os.makedirs(os.path.dirname(spv_path), exist_ok=True)

    cmd = '{} {} -o {} --target-env=opengl'.format(tool_path.get_glslc_path(), os.path.abspath(glsl_path), os.path.abspath(spv_path))

    print('call: {}\n'.format(cmd))
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    if len(result.stdout) > 0:
        print('[spirv-cross] {}\n'.format(result.stdout))

    if len(result.stderr) > 0:
        print('[spirv-cross] {}\n'.format(result.stderr))

    pass
