 嵌入式STM32工程框架参考

## 软/硬件工具

- 开发对象:C板(STM32F407)
- 软件工具:STM32CubeMX+STM32CubeCLT+CLion
[视频教学](https://www.bilibili.com/video/BV1pnjizYEAk/?spm_id_from=333.337.search-card.all.click&vd_source=bac180abef9ba0c773fe14d848ce89e0)
- 烧录工具:CMSIS_DAP[配置教学!!教学有需要修改的地方](https://www.cnblogs.com/xs314/articles/18906035/stm32_daplink_clion)

## 文件架构

- User:所有人为编写的文件
  - cfg:config各类配置文件,包括dap下载器配置

## CMakeLists修改

```cmake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
```

```cmake
enable_language(C CXX ASM)
```

```cmake
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user sources here
        User/Task/ReadTask.c
        User/Drive/drv_can.c
        User/Drive/drv_uart.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined include paths
        User/Algorithm
        User/Device
        User/Drive
        User/Task
)
```

# 未知TODO

7处，why存文件传输助手