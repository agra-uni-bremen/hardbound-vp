add_executable(hifive-vp
        hifive_main.cpp
        can.cpp
        oled.cpp
        gpio.cpp
        torture_slip.cpp
        gpio/gpiocommon.cpp
        gpio/gpio-server.cpp
        gpio/gpio-client.cpp
        ../../util/elegantEnums.cpp #sorry :(
        oled/common.cpp
        ${HEADERS})

target_link_libraries(hifive-vp rv32 platform-common gdb-mc ${Boost_LIBRARIES} ${SystemC_LIBRARIES} pthread)

INSTALL(TARGETS hifive-vp RUNTIME DESTINATION bin)
