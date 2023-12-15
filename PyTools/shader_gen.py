import os.path
import shader_compile.shader
import json
import subprocess
import shutil


def clear_dir(directory_path: str) -> None:
    if not os.path.exists(directory_path):
        return

    for filename in os.listdir(directory_path):
        file_path = os.path.join(directory_path, filename)
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)


def hlsl_dxc_compile(dxc_path: str, hlsl_src_path: str, bin_path: str, is_spirv: bool) -> None:
    if is_spirv:
        print('\n\nBegin dxc compile hlsl to spir-v bin...\n\n')
    else:
        print('\n\nBegin dxc compile hlsl to dx bin...\n\n')

    clear_dir(bin_path)

    for root, dir_list, file_list in os.walk(hlsl_src_path):
        for file_name in file_list:
            file_suffix: str = file_name.split('.')[-1]
            if file_suffix != 'hlsl':
                continue

            print('\thlsl src: {}'.format(file_name))

            src_dir: str = root
            src_full_path: str = src_dir + '/' + file_name

            if is_spirv:
                bin_name = file_name.replace('.hlsl', '.spv')
            else:
                bin_name = file_name.replace('.hlsl', '.bin')

            bin_dir = bin_path + src_dir.lstrip(hlsl_src_path)
            bin_full_path: str = bin_dir + '/' + bin_name
            os.makedirs(bin_dir, exist_ok=True)

            cmd = dxc_path
            if '.Vertex.' in file_name:
                cmd += ' -T vs_6_0 '
            elif '.Pixel.' in file_name:
                cmd += ' -T ps_6_0 '
            else:
                print('\tERROR! src no shader type: {}'.format(file_name))

            cmd += '-E main -Fo {}'.format(os.path.abspath(bin_full_path))

            if is_spirv:
                cmd += ' -spirv'

            cmd += ' {}'.format(os.path.abspath(src_full_path))

            print('\tcall: {}'.format(cmd))
            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

            if len(result.stdout) > 0:
                print('\t\t[dxc] {}'.format(result.stdout))

            if len(result.stderr) > 0:
                print('\t\t[dxc] {}'.format(result.stderr))
    pass


def hlsl_dxc_dx_compile(dxc_path: str, hlsl_src_path: str, dx_bin_path: str) -> None:
    hlsl_dxc_compile(dxc_path, hlsl_src_path, dx_bin_path, False)
    pass


def hlsl_dxc_spirv_compile(dxc_path: str, hlsl_src_path: str, spirv_bin_path: str) -> None:
    hlsl_dxc_compile(dxc_path, hlsl_src_path, spirv_bin_path, True)
    pass


def spirv_disassemble(spirv_cross_path: str, spirv_bin_path: str, glsl_src_path: str) -> None:
    print('\n\nBegin disassemble spir-v bin...\n\n')
    clear_dir(glsl_src_path)

    for root, dir_list, file_list in os.walk(spirv_bin_path):
        for file_name in file_list:
            file_suffix: str = file_name.split('.')[-1]
            if file_suffix != 'spv':
                continue

            spv_dir: str = root
            spv_full_path: str = spv_dir + '/' + file_name

            glsl_name = file_name.replace('.spv', '.glsl')
            glsl_dir = glsl_src_path + spv_dir.lstrip(spirv_bin_path)
            glsl_full_path: str = glsl_dir + '/' + glsl_name
            os.makedirs(glsl_dir, exist_ok=True)

            cmd = '{} {}'.format(spirv_cross_path, spv_full_path)

            print('\tcall: {}'.format(cmd))
            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

            if len(result.stdout) > 0:
                with open(glsl_full_path, 'w') as file:
                    file.write(result.stdout)

            if len(result.stderr) > 0:
                print('\t\t[spirv-cross] {}'.format(result.stderr))

    pass


def main() -> None:
    vk_bin_path: str = shader_compile.shader.get_os_vulkan_path() + '/Bin/'
    dxc_path: str = vk_bin_path + 'dxc.exe'
    spirv_cross_path: str = vk_bin_path + 'spirv-cross.exe'

    if not os.path.exists(dxc_path):
        print('dxc.exe path error: {}'.format(dxc_path))
        return

    if not os.path.exists(spirv_cross_path):
        print('spirv-cross.exe path error: {}'.format(spirv_cross_path))
        return

    config_file: str = 'shader_gen_config.json'
    with open(config_file, 'r', encoding='utf-8') as fp:
        shader_gen_config_array = json.load(fp)['ShaderCodeGenPath']
        for shader_gen_config in shader_gen_config_array:
            hlsl_src_path: str = shader_gen_config['HlslSourceDir']
            dx_bin_path: str = shader_gen_config['DxBinTargetDir']
            spirv_bin_path: str = shader_gen_config['SpirvBinTargetDir']
            glsl_src_path: str = shader_gen_config['GlslTargetDir']
            hlsl_dxc_dx_compile(dxc_path, hlsl_src_path, dx_bin_path)
            hlsl_dxc_spirv_compile(dxc_path, hlsl_src_path, spirv_bin_path)
            spirv_disassemble(spirv_cross_path, spirv_bin_path, glsl_src_path)


if __name__ == '__main__':
    main()

