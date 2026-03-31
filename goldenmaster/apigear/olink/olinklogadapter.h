/*
* MIT License
*
* Copyright (c) 2021 ApiGear
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

#include "private/apigear_olink.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include "olink/core/types.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
#include "apigear/utilities/logger.h"

namespace ApiGear {
namespace Utilities {

/**
 * @brief maps the LogLevel from the Olink core lib to the generic template version
 * 
 * @param level ObjectLink log level
 * @return LogLevel generic utilities log level
 */
LogLevel APIGEAR_OLINK_EXPORT mapLogLevel(ObjectLink::LogLevel level) {
    switch(level) {
         case ObjectLink::LogLevel::Debug: return LogLevel::Debug;
         case ObjectLink::LogLevel::Info: return LogLevel::Info;
         case ObjectLink::LogLevel::Warning: return LogLevel::Warning;
         case ObjectLink::LogLevel::Error: return LogLevel::Error;
         // if we don't know the level, assume it is only for debugging purposes
         default: return LogLevel::Debug;
    }
}

/**
 * @brief maps the writelogfunc from the generic template to the Olink core lib version
 * 
 * @param func generic log func from the template
 * @return ObjectLink::WriteLogFunc ObjectLink specific for olink logger
 */
ObjectLink::WriteLogFunc APIGEAR_OLINK_EXPORT logAdapter(WriteLogFunc func)
{
    return [func](ObjectLink::LogLevel level, const std::string& msg){
        if (func) {
            func(mapLogLevel(level), msg);
        }
    };
}

} // namespace ApiGear
} // namespace Utilities
