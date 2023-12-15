import os.path
import shader_compile.shader


def hlsl_dxc_dx_compile(dxc_path: str, hlsl_src_path: str, dx_bin_path: str) -> None:
    pass


def hlsl_dxc_spirv_compile(dxc_path: str, hlsl_src_path: str, spirv_bin_path: str) -> None:
    pass


def spirv_disassemble(spirv_dis_path: str, spirv_bin_path: str, glsl_src_path: str) -> None:
    pass


def main() -> None:
    vk_bin_path: str = shader_compile.shader.get_os_vulkan_path() + '/Bin/'
    dxc_path: str = vk_bin_path + 'dxc.exe'
    spirv_dis_path: str = vk_bin_path + 'spirv-dis.exe'

    if not os.path.exists(dxc_path):
        print('dxc.exe path error: {}'.format(dxc_path))
        return

    if not os.path.exists(spirv_dis_path):
        print('spirv-dis.exe path error: {}'.format(spirv_dis_path))
        return


if __name__ == '__main__':
    main()

