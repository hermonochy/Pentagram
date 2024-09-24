#pragma once

enum vsyncFlags {
    PNT_VSYNC_FLAGS_ADAPTIVE = -1,
    PNT_VSYNC_FLAGS_OFF,
    PNT_VSYNC_FLAGS_ON,
};

enum eventCallbackFlags {
    PNT_EVENT_TYPE_KEYBOARD,
    PNT_EVENT_TYPE_CHAR,
    PNT_EVENT_TYPE_DROP,
    PNT_EVENT_TYPE_SCROLL,
    PNT_EVENT_TYPE_CURSORPOS,
    PNT_EVENT_TYPE_WINDOWPOS,
    PNT_EVENT_TYPE_WINDOWSIZE,
    PNT_EVENT_TYPE_CURSORENTER,
    PNT_EVENT_TYPE_MOUSEBUTTON,
    PNT_EVENT_TYPE_WINDOWFOCUS,
    PNT_EVENT_TYPE_ICONIFY
};
