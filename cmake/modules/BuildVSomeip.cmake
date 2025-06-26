function(BuildVSomeip)
    set(SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/vsomeip")
    set(BUILD_DIR  "${CMAKE_BINARY_DIR}/vsomeip-build")
    set(INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdparty")

    if (EXISTS ${INSTALL_DIR}/include/vsomeip)
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
	    -DVSOMEIP_INSTALL_ROUTINGMANAGERD=ON
	    -DGTEST_ROOT=n/a
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DBOOST_ROOT=${INSTALL_DIR}
        -DENABLE_SIGNAL_HANDLING=1
        ${RPATH_OPTIONS}
    )

    execute_process(
        COMMAND ${CMAKE_CONFIG_CMD}
        RESULT_VARIABLE CONFIG_RESULT
    )

    if(NOT CONFIG_RESULT EQUAL 0)
        message(FATAL_ERROR "VSomeip CMake configuration failed with code ${CONFIG_RESULT}")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${BUILD_DIR} --target install
        RESULT_VARIABLE BUILD_RESULT
    )

    if (NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "VSomeip build failed with code ${BUILD_RESULT}")
    endif()
endfunction()
