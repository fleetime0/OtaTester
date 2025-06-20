function(BuildBoost)
    set(SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/boost")
    set(BUILD_DIR  "${CMAKE_BINARY_DIR}/boost-build")
    set(INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdparty")
    set(COMPONENTS "system,thread,filesystem")

    if (EXISTS ${INSTALL_DIR}/include/boost)
        return()
    endif()

    file(COPY ${SRC_DIR}/ DESTINATION ${BUILD_DIR})

    set(BOOST_BOOTSTRAP_CMD ./bootstrap.sh --with-libraries=${COMPONENTS} --prefix=${INSTALL_DIR})

    if (CMAKE_TOOLCHAIN_FILE)
        set(BACKUP_CC $ENV{CC})
        set(BACKUP_CXX $ENV{CXX})
        set(ENV{CC} "gcc")
        set(ENV{CXX} "g++")
        execute_process(
            COMMAND ${BOOST_BOOTSTRAP_CMD}
            WORKING_DIRECTORY ${BUILD_DIR}
        )
        set(ENV{CC} ${BACKUP_CC})
        set(ENV{CXX} ${BACKUP_CXX})
    else()
        execute_process(
            COMMAND ${BOOST_BOOTSTRAP_CMD}
            WORKING_DIRECTORY ${BUILD_DIR}
        )
    endif()

    if (CMAKE_TOOLCHAIN_FILE)
        file(READ ${BUILD_DIR}/project-config.jam BOOST_CONFIG)
        if (CROSS_TOOLS_PATH)
            string(REGEX REPLACE "using gcc ;"
                "using gcc : arm64 : ${CROSS_TOOLS_PATH}/bin/aarch64-linux-gnu-gcc ;"
                UPDATED_BOOST_CONFIG
                "${BOOST_CONFIG}")
        else()
            string(REGEX REPLACE "using gcc ;"
                "using gcc : arm64 : aarch64-linux-gnu-gcc ;"
                UPDATED_BOOST_CONFIG
                "${BOOST_CONFIG}")
        endif()
        file(WRITE ${BUILD_DIR}/project-config.jam "${UPDATED_BOOST_CONFIG}")
    endif()
    
    if (CMAKE_BUILD_TYPE)
        string(TOLOWER "${CMAKE_BUILD_TYPE}" BOOST_BUILD_TYPE)
    else()
        set(BOOST_BUILD_TYPE "release")
    endif()

    set(BOOST_BUILD_CMD ./b2 variant=${BOOST_BUILD_TYPE} link=shared install cxxflags=-fPIC linkflags=-Wl,-rpath=\$ORIGIN/../lib)

    execute_process(
        COMMAND ${BOOST_BUILD_CMD}
        WORKING_DIRECTORY ${BUILD_DIR}
    )
endfunction()
