#!/usr/bin/env ruby
#
# proxy.rb [HOST_IP_ADDRESS LISTEN_PORT]
# - HOST_IP_ADDRESS: if not set or "" or "-" is set, IP is obtained.
# - LISTEN_PORT: 8080 is set by default
# 
# this proxy server emulates narrow band network.
# sleep 100 (ms) by default for everytime 4KB block is sent to client.
#

require 'webrick'
require 'webrick/httpproxy'
include WEBrick


#$HOST_IP_ADDRESS = "127.0.0.1"
$HOST_IP_ADDRESS = "43.2.152.108"
$LISTEN_PORT = 8080

puts("")
puts("start server. available url:")
puts("start proxy server!")
puts("- host ip: " + $HOST_IP_ADDRESS)
puts("- port no: " + $LISTEN_PORT.to_s)

port_string = ""
if $LISTEN_PORT != 80
	port_string = ":" + $LISTEN_PORT.to_s
end


module WEBrick
  class HTTPResponse
    def _write_data(socket, data)
		#sleep 0.1
#		sleep $DELAY_TIME_MS / 1000.0
		socket << data
		socket.flush
    end
  end
end

s = HTTPProxyServer.new({ :BindAddress => $HOST_IP_ADDRESS, :Port => $LISTEN_PORT })
trap("INT"){ s.shutdown }
s.start
