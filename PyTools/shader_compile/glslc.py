import subprocess
import util


def compile_glsl(glsl_path: str) -> None:
    print('\tglslc compile {}'.format(glsl_path))
    spv_path: str = glsl_path + 'spv'

    cmd = '{} {} -o {}'.format(util.get_glslc_path(), glsl_path, spv_path)

    print('\tcall: {}'.format(cmd))
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    if len(result.stdout) > 0:
        print('\t\t[spirv-cross] {}'.format(result.stdout))

    if len(result.stderr) > 0:
        print('\t\t[spirv-cross] {}'.format(result.stderr))

    pass
