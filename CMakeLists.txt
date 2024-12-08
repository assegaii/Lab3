cmake_minimum_required(VERSION 3.10)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 1.0.${PATCH_VERSION})

# Для Debug:
set(CMAKE_CXX_FLAGS_DEBUG "-static-libgcc -static-libstdc++ -std=gnu++14")

# Для Release:
set(CMAKE_CXX_FLAGS_RELEASE "-static-libgcc -static-libstdc++ -std=gnu++14")

# Указываем имя проекта, версию и язык
project(container VERSION ${PROJECT_VESRION})


set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем директорию для заголовочных файлов
include_directories(include)

# Для Windows
if(WIN32)
    # Настройки для компиляции под Windows
    add_executable(container main.cpp)


    # Установка исполняемых файлов
    install(TARGETS container DESTINATION bin)
    
    set(CPACK_GENERATOR NSIS)
    set(CPACK_PACKAGE_EXECUTABLES "container.exe" "container")
    set(CPACK_PACKAGE_FILE_NAME "container-${PROJECT_VERSION}-Windows")
    

elseif(UNIX)
    # Для Linux (Ubuntu)
    add_executable(container main.cpp)

    set(CPACK_GENERATOR DEB)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dmitryanons@gmail.com)


# Включаем тестирование
include(CTest)
enable_testing()




# Настройки для пакета
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

