#pragma once

#if _DEBUG
    #define DEBUG_LOG(fmt, ...) \
        char ftm_buffer[8096]; \
        sprintf_s(ftm_buffer, sizeof(ftm_buffer), fmt, __VA_ARGS__); \
        sprintf_s(ftm_buffer, sizeof(ftm_buffer), "%s\n", fmt); \
        OutputDebugStringA(ftm_buffer);
#else
    #define DEBUG_LOG(...)
#endif