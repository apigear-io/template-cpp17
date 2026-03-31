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

#include "olinkhost.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include "olink/remoteregistry.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
#include <iostream>
#include "private/requesthandlerfactory.h"
#include "utilities/logger.h"

using namespace ApiGear::PocoImpl;

OLinkHost::OLinkHost(ApiGear::ObjectLink::RemoteRegistry& registry, const ApiGear::ObjectLink::WriteLogFunc& logFunc)
    : m_connectionStorage(registry, logFunc)
{}

OLinkHost::~OLinkHost()
{
    close();
}

void OLinkHost::listen(int port)
{
    // Poco::Net::HttpServer takes ownership of Request Handler Factory
    m_webserver = std::make_unique<Poco::Net::HTTPServer>(new RequestHandlerFactory(m_connectionStorage), port);
    AG_LOG_INFO("wss.listen() on " + std::to_string(m_webserver->port()));
    m_webserver->start();
}

void OLinkHost::close()
{
    m_connectionStorage.closeConnections();
    if (m_webserver)
    {
        m_webserver->stop();
    }
    AG_LOG_INFO("wss.closed()");
}
