import os


def get_os_vulkan_path() -> str:
    return os.environ.get('VK_SDK_PATH')
