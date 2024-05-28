#pragma once

enum loggerFlags : unsigned char {
    PNT_LOGGER_FLAGS_NOTE,
    PNT_LOGGER_FLAGS_WARNING,
    PNT_LOGGER_FLAGS_ERROR,
    PNT_LOGGER_FLAGS_FATAL
};

enum vsyncFlags : char {
    PNT_VSYNC_FLAGS_ADAPTIVE = -1,
    PNT_VSYNC_FLAGS_OFF,
    PNT_VSYNC_FLAGS_ON,
};

enum callbackFlags : unsigned char {
    PNT_CALLBACK_FLAGS_STARTFRAME,
    PNT_CALLBACK_FLAGS_ENDFRAME,
    PNT_CALLBACK_FLAGS_COUNT,
};

enum eventCallbackFlags : unsigned char {
    PNT_EVENT_TYPE_KEYBOARD,
    PNT_EVENT_TYPE_MOUSE
};
