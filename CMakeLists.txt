cmake_minimum_required(VERSION 3.11)

project(LinkedListApp CXX)

set(CMAKE_CXX_STANDARD 23)

# Специфичные настройки для компилятора Visual Studio
if(MSVC)
    # Генерируем статическую заглушку для динамических библиотек
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # Включаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Подключаем googletest
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Объявляем библиотеки
add_library(hashTable_lib SHARED "include/hashTable.cpp")
target_include_directories(hashTable_lib PUBLIC "include")

# Объявляем тесты
add_executable(hashTable_test "test/hash_test.cpp")
target_link_libraries(hashTable_test hashTable_lib GTest::gtest_main)

# Объявляем консольное приложение
add_executable(app "app/main.cpp")
target_link_libraries(app hashTable_lib)