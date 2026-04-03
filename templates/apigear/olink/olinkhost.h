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

#include "Poco/Net/HTTPServer.h"
#include "private/connectionstorage.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include "olink/core/types.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#include <memory>


#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define APIGEAR_OLINK_EXPORT __attribute__ ((dllexport))
#else
#define APIGEAR_OLINK_EXPORT __declspec(dllexport)
#endif
#else
#if __GNUC__ >= 4
#define APIGEAR_OLINK_EXPORT __attribute__ ((visibility ("default")))
#else
#define APIGEAR_OLINK_EXPORT
#endif
#endif

namespace ApiGear {
namespace PocoImpl {


/**
* Class that hosts a server for olink services.
* Stores connections requested by clients and provides connection endpoints used by sources to the registry.
* May hold multiple connections. 
*/
class APIGEAR_OLINK_EXPORT OLinkHost
{
public:
    /** ctor
    * @param registry A global registry to which network endpoints for sources are added.
    * @param logFunc The function to be used for logging inside the objectlink core remote nodes.
    */
    explicit OLinkHost(ApiGear::ObjectLink::RemoteRegistry& registry, const ApiGear::ObjectLink::WriteLogFunc& logFunc);
    /**dtor*/
    virtual ~OLinkHost();
    /** Starts a server and puts it in a listen state.
    * @param port A port number on which the server should listen.
    */
    void listen(int port);
    /** Returns the port the server is listening on (useful when listen(0) was used). */
    int port() const;
    /* Close the server and all connections. */
    void close();

private:
    /** A server used for connections.*/
    std::unique_ptr<Poco::Net::HTTPServer> m_webserver;
    /** Storage for connections.*/
    ConnectionStorage m_connectionStorage;
};

} // namespace PocoImpl
} // namespace ApiGear
