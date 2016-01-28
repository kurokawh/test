#!/usr/bin/env ruby
#
# no_content_length_server.rb [HOST_IP_ADDRESS LISTEN_PORT]
# - HOST_IP_ADDRESS: if not set or "" or "-" is set, IP is obtained.
# - LISTEN_PORT: 8080 is set by default
#
# this proxy server emulates narrow band network.
# sleep 100 (ms) by default for everytime 4KB block is sent to client.
#


require 'webrick'
require 'webrick/httpproxy'
include WEBrick

$HOST_IP_ADDRESS = "127.0.0.1"
$LISTEN_PORT = 8080

puts("")
puts("start proxy server!")
puts("- host ip: " + $HOST_IP_ADDRESS)
puts("- port no: " + $LISTEN_PORT.to_s)
puts("proxy setting:")
port_string = ""
if $LISTEN_PORT != 80
	port_string = ":" + $LISTEN_PORT.to_s
end
puts("  http://"+$HOST_IP_ADDRESS + port_string)
puts("signal ctrl-c to stop server.")
puts("")


# rewrite HTTPResponse::send_header so that 
# 'Content-Length' is not sent to client.
# NOTE: this API is called after handler returns.
module WEBrick
  class HTTPResponse
    def send_header(socket)
      if @http_version.major > 0
        data = status_line()
        @header.each{|key, value|
		  if key == 'content-length'
			  puts("skip sending content length: " + value.to_s)
			  next
		  end
          tmp = key.gsub(/\bwww|^te$|\b\w/){|s| s.upcase }
          data << "#{tmp}: #{value}" << CRLF
        }
        @cookies.each{|cookie|
          data << "Set-Cookie: " << cookie.to_s << CRLF
        }
        data << CRLF
        _write_data(socket, data)
      end
    end
  end
end

=begin
# this does not work because
# WEBrick::HTTPResponse::setup_header set content-length
# if res::body is not IO.
handler = Proc.new() {|req,res|
	cl = res.header['content-length']
	if (cl == nil)
		puts("no content-length")
	else
		puts("content-length: " + cl)
	end
	res.header.delete('content-length')
}
=end

s = HTTPProxyServer.new({:BindAddress => $HOST_IP_ADDRESS,
							:Port => $LISTEN_PORT})
#							:ProxyContentHandler => handler})
trap("INT"){ s.shutdown }
s.start
