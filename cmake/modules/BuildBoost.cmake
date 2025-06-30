function(BuildBoost)
    set(SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/boost")
    set(BUILD_DIR "${CMAKE_BINARY_DIR}/boost-build")
    set(INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdparty")
    if(WIN32)
        set(COMPONENTS "system\;thread\;filesystem\;asio\;icl\;property_tree\;foreach\;log")
    else()
        set(COMPONENTS "system\;thread\;filesystem\;asio\;icl\;property_tree\;foreach")
    endif()

    if (EXISTS "${INSTALL_DIR}/include/boost")
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

    execute_process(
        COMMAND ${CMAKE_COMMAND}
            -S ${SRC_DIR}
            -B ${BUILD_DIR}
            -DBUILD_SHARED_LIBS=ON
            -DBOOST_INSTALL_LAYOUT=system
            -DBOOST_INCLUDE_LIBRARIES=${COMPONENTS}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
            ${RPATH_OPTIONS}
        RESULT_VARIABLE CONFIG_RESULT
    )

    if(NOT CONFIG_RESULT EQUAL 0)
        message(FATAL_ERROR "Boost CMake configuration failed with code ${CONFIG_RESULT}")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --target install
        RESULT_VARIABLE BUILD_RESULT
    )

    if (NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "Boost build failed with code ${BUILD_RESULT}")
    endif()
endfunction()
