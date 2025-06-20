function(BuildVSomeip)
    set(SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/vsomeip")
    set(BUILD_DIR  "${CMAKE_BINARY_DIR}/vsomeip-build")
    set(INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdparty")

    if (EXISTS ${INSTALL_DIR}/include/vsomeip)
        return()
    endif()

    set(CMAKE_CONFIG_CMD ${CMAKE_COMMAND}
        -S ${SRC_DIR} 
        -B ${BUILD_DIR}
	    -DVSOMEIP_INSTALL_ROUTINGMANAGERD=ON
	    -DGTEST_ROOT=n/a
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DBOOST_ROOT=${INSTALL_DIR}
        -DENABLE_SIGNAL_HANDLING=1
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
