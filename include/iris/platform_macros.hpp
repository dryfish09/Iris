#pragma once

#ifdef _WIN32
#define Iris_Platform_Windows
#endif

#if defined(__linux__) && !defined(__ANDROID__)
#define Iris_Platform_Linux
#endif

#if defined(__MACH__) || defined(__APPLE__)
#define Iris_Platform_Darwin
#endif

#ifdef __ANDROID__
#define Iris_Platform_Android
#endif

#ifdef __EMSCRIPTEN__
#define Iris_Platform_Web
#endif

#if defined(Iris_Platform_Windows) || defined(Iris_Platform_Linux) || defined(Iris_Platform_Darwin)
#define Iris_Platform_Desktop
#endif

#if defined(Iris_Platform_Android)
#define Iris_Platform_Mobile
#endif
