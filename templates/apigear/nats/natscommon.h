#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
  #define APIGEAR_NATS_EXPORT __attribute__ ((dllexport))
#else
  #define APIGEAR_NATS_EXPORT __declspec(dllexport)
#endif
#else
  #if __GNUC__ >= 4
    #define APIGEAR_NATS_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define APIGEAR_NATS_EXPORT
  #endif
#endif
