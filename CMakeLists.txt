cmake_minimum_required(VERSION 3.0)
project(WinUI3Sample)

function(nuget_install package version dir out_dir)
    execute_process(
        COMMAND nuget install ${package} -Version ${version} -OutputDirectory "${dir}"
        RESULT_VARIABLE result
        ERROR_VARIABLE error
    )

    if(NOT result EQUAL 0)
        message(FATAL_ERROR "nuget_install: Failed to install ${arg1}.${arg2}: ${error}")
    else()
        set(${out_dir} "${dir}/${package}.${version}" PARENT_SCOPE)
    endif()
endfunction()

set(TARGET WinUI3Standalone)

# Target
add_executable(${TARGET} WIN32
    src/pch.cpp
    src/main.cpp
    src/MyApplication.cpp src/MyApplication.h
    src/MainWindow.cpp src/MainWindow.h
)

# Target Configuration
target_precompile_headers(${TARGET} PRIVATE src/pch.h)
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 23)

# Dependencies
nuget_install("Microsoft.WindowsAppSDK" "1.5.240311000" "${CMAKE_CURRENT_BINARY_DIR}/packages" WindowsAppSDK_DIR)
nuget_install("Microsoft.Windows.CppWinRT" "2.0.240405.15" "${CMAKE_CURRENT_BINARY_DIR}/packages" CppWinRT_DIR)

execute_process(
    COMMAND "${CppWinRT_DIR}/bin/cppwinrt.exe" -optimize -input "${WindowsAppSDK_DIR}/lib/uap10.0" -input "${WindowsAppSDK_DIR}/lib/uap10.0.18362" -input sdk -output "${CMAKE_CURRENT_BINARY_DIR}/Generated Files"
    RESULT_VARIABLE result
    ERROR_VARIABLE error
)

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    "${WindowsAppSDK_DIR}/runtimes/win10-x64/native/Microsoft.WindowsAppRuntime.Bootstrap.dll"
    "$<TARGET_FILE_DIR:${TARGET}>"
)

# Includes
target_include_directories(${TARGET} PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${WindowsAppSDK_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}/Generated Files"
)

# Linking
target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
target_link_directories(${TARGET} PRIVATE "${WindowsAppSDK_DIR}/lib/win10-x64")
target_link_libraries(${TARGET}
    Microsoft.WindowsAppRuntime.Bootstrap
    Microsoft.WindowsAppRuntime
    WindowsApp 
    ole32
    oleaut32
)