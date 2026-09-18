#pragma once

#if !defined(NAssert_Log) || !defined(NAssert_Terminate)
#error Define NAssert_Log and NAssert_Terminate to use NAssert
#endif

#define NAssert_Stringify(x) #x
#define NAssert_Stringify_Wrapper(x) NAssert_Stringify(x)

#define NAssert_Implementation_Message(condition, message) \
    if (!(condition)) { \
        NAssert_Log("Assertion Failed: " NAssert_Stringify_Wrapper(condition)); \
        NAssert_Log(message); \
        NAssert_Terminate(); \
    }

#define NAssert_Implementation_NoMessage(condition) \
    if (!(condition)) { \
        NAssert_Log("Assertion Failed: " NAssert_Stringify_Wrapper(condition)); \
        NAssert_Terminate(); \
    }

#ifdef NAssert_Config_AssertMessage
#define NAssert NAssert_Implementation_Message
#else // NAssert_Config_AssertNoMessage (Default)
#define NAssert NAssert_Implementation_NoMessage
#endif
