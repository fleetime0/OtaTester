function(BuildCommonAPI)
    set(SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/capicxx-core-runtime")
    set(BUILD_DIR "${CMAKE_BINARY_DIR}/capicxx-core-runtime-build")
    set(INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdparty")

    if (EXISTS ${INSTALL_DIR}/include/CommonAPI-3.2)
        return()
    endif()

    set(CMAKE_CONFIG_CMD ${CMAKE_COMMAND}
        -S ${SRC_DIR}
        -B ${BUILD_DIR}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=ON
        -DCMAKE_INSTALL_RPATH=$ORIGIN/../lib
    )

    execute_process(
        COMMAND ${CMAKE_CONFIG_CMD}
    )

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR} --target install
    )
endfunction()
