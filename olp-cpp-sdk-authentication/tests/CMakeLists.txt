# Copyright (C) 2019 HERE Europe B.V.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0
# License-Filename: LICENSE

set(OLP_AUTHENTICATION_TEST_SOURCES
    AuthenticationCredentialsTest.cpp
    AuthenticationClientTest.cpp
    DecisionApiClientTest.cpp
    CryptoTest.cpp
)

if (ANDROID OR IOS)
    set(OLP_SDK_AUTHENTICATION_TESTS_LIB olp-cpp-sdk-authentication-tests-lib)

    add_library(${OLP_SDK_AUTHENTICATION_TESTS_LIB}
        ${OLP_AUTHENTICATION_TEST_SOURCES}
    )

    target_link_libraries(${OLP_SDK_AUTHENTICATION_TESTS_LIB}
    PRIVATE
        gtest
        olp-cpp-sdk-authentication
    )

    # For internal testing
    target_include_directories(${OLP_SDK_AUTHENTICATION_TESTS_LIB}
    PRIVATE
        ${${PROJECT_NAME}_SOURCE_DIR}/src
    )

    if (ANDROID)
        include(${CMAKE_SOURCE_DIR}/cmake/android/gen_android_test.cmake)
        gen_android_test_runner(olp-cpp-sdk-authentication-tests
            ${OLP_SDK_AUTHENTICATION_TESTS_LIB})
        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/android
            ${CMAKE_CURRENT_BINARY_DIR}/android)

    else()
        include(${CMAKE_SOURCE_DIR}/cmake/ios/gen_ios_test.cmake)
        gen_ios_test_runner(olp-cpp-sdk-authentication-tests
            ${OLP_SDK_AUTHENTICATION_TESTS_LIB})
        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/ios
            ${CMAKE_CURRENT_BINARY_DIR}/ios)

    endif()

else()
    add_executable(olp-cpp-sdk-authentication-tests
        ${OLP_AUTHENTICATION_TEST_SOURCES}
    )

    target_link_libraries(olp-cpp-sdk-authentication-tests
        PRIVATE
            gtest_main
            olp-cpp-sdk-authentication
    )

    # For internal testing
    target_include_directories(olp-cpp-sdk-authentication-tests
    PRIVATE
        ${${PROJECT_NAME}_SOURCE_DIR}/src
    )
endif()
