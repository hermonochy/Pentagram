#pragma once

enum loggerFlags : unsigned char
{
    PNT_LOGGER_FLAGS_NOTE,
    PNT_LOGGER_FLAGS_WARNING,
    PNT_LOGGER_FLAGS_ERROR,
    PNT_LOGGER_FLAGS_FATAL
};

enum vsyncFlags : char
{
    PNT_VSYNC_FLAGS_ADAPTIVE = -1,
    PNT_VSYNC_FLAGS_OFF,
    PNT_VSYNC_FLAGS_ON,
};

enum listenerFlags : unsigned char
{
    PNT_LISTENER_FLAGS_EVENT,
    PNT_LISTENER_FLAGS_STARTFRAME,
    PNT_LISTENER_FLAGS_ENDFRAME
};
