//
// UDPEchoServer.cpp
//
// $Id: //poco/1.4/Net/testsuite/src/UDPEchoServer.cpp#1 $
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "UDPEchoServer.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Timespan.h"
#include <iostream>


using Poco::Net::Socket;
using Poco::Net::DatagramSocket;
using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;


UDPEchoServer::UDPEchoServer():
	_thread("UDPEchoServer"),
	_stop(false)
{
	_socket.bind(SocketAddress(), true);
	_thread.start(*this);
	_ready.wait();
}


UDPEchoServer::UDPEchoServer(const SocketAddress& sa):
	_thread("UDPEchoServer"),
	_stop(false)
{
	_socket.bind(sa, true);
	_thread.start(*this);
	_ready.wait();
}


UDPEchoServer::~UDPEchoServer()
{
	_stop = true;
	_thread.join();
}


Poco::UInt16 UDPEchoServer::port() const
{
	return _socket.address().port();
}


void UDPEchoServer::run()
{
	Poco::Timespan span(250000);
	while (!_stop)
	{
		_ready.set();
		if (_socket.poll(span, Socket::SELECT_READ))
		{
			try
			{
				char buffer[256];
				SocketAddress sender;
				int n = _socket.receiveFrom(buffer, sizeof(buffer), sender);
				n = _socket.sendTo(buffer, n, sender);
			}
			catch (Poco::Exception& exc)
			{
				std::cerr << "UDPEchoServer: " << exc.displayText() << std::endl;
			}
		}
	}
}


SocketAddress UDPEchoServer::address() const
{
	return _socket.address();
}
