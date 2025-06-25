function(BuildCommonAPIVSomeip)
    set(SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/capicxx-someip-runtime")
    set(BUILD_DIR  "${CMAKE_BINARY_DIR}/capicxx-someip-runtime-build")
    set(INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdparty")

    if (EXISTS ${INSTALL_DIR}/include/CommonAPI-3.2/CommonAPI/SomeIP)
        return()
    endif()

    if(WIN32)
        set(RPATH_OPTIONS "")
    else()
        set(RPATH_OPTIONS
            -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=ON
            -DCMAKE_INSTALL_RPATH=$ORIGIN/../lib
        )
    endif()

    set(CMAKE_CONFIG_CMD ${CMAKE_COMMAND}
        -S ${SRC_DIR}
        -B ${BUILD_DIR}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DCMAKE_PREFIX_PATH=${INSTALL_DIR}
        -DUSE_INSTALLED_COMMONAPI=ON
        ${RPATH_OPTIONS}
    )

    execute_process(
        COMMAND ${CMAKE_CONFIG_CMD}
        RESULT_VARIABLE CONFIG_RESULT
    )

    if(NOT CONFIG_RESULT EQUAL 0)
        message(FATAL_ERROR "CommonAPIVSomeip CMake configuration failed with code ${CONFIG_RESULT}")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR} --target install
        RESULT_VARIABLE BUILD_RESULT
    )

    if (NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "CommonAPIVSomeip build failed with code ${BUILD_RESULT}")
    endif()
endfunction()
