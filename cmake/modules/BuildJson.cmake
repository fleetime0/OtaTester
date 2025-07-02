function(BuildJson)
    set(SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/nlohmann_json")
    set(BUILD_DIR "${CMAKE_BINARY_DIR}/nlohmann_json-build")
    set(INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdparty")

    if (EXISTS ${INSTALL_DIR}/include/nlohmann)
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
        -DBUILD_SHARED_LIBS=ON
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DJSON_BuildTests=OFF
        ${RPATH_OPTIONS}
    )

    execute_process(
        COMMAND ${CMAKE_CONFIG_CMD}
        RESULT_VARIABLE CONFIG_RESULT
    )

    if(NOT CONFIG_RESULT EQUAL 0)
        message(FATAL_ERROR "Json CMake configuration failed with code ${CONFIG_RESULT}")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR} -j2 --target install
        RESULT_VARIABLE BUILD_RESULT
    )

    if (NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "Json build failed with code ${BUILD_RESULT}")
    endif()
endfunction()
