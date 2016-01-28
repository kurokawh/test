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
puts("  http://"+$HOST_IP_ADDRESS + port_string + "/control?KEY=VAL")
puts("     status=503")
puts("     sleep=10 (sec)")
puts("     cl=on|off")
puts("     sn=on|off")
puts("signal ctrl-c to stop server.")
puts("")


# parse path and return last part
# /a/b/c/d/1=> 1 (int)
def parse_path (path)
	basename = File::basename(path)
	return basename.to_i
end

CONTROL_ERROR_STATUS = 0
CONTROL_SLEEP_TIME = 0 # (sec)
CONTROL_NO_CONTENT_LENGTH = false
CONTROL_SLOW_NETWORK = false
shutdown_called = false


# rewrite HTTPResponse::send_header so that 
# 'Content-Length' is not sent to client.
# NOTE: this API is called after handler returns.
module WEBrick
	class HTTPResponse

		alias old_write_data _write_data
		def _write_data(socket, data)
			if !CONTROL_SLOW_NETWORK
				return old_write_data(socket, data)
			end
			#sleep 0.1
			puts("<TEST SERVER> slow network")
			sleep 0.1
			socket << data
			socket.flush
		end

		alias old_send_header send_header
		def send_header(socket)
			if !CONTROL_NO_CONTENT_LENGTH
				return old_send_header(socket)
			end
			puts("<TEST SERVER> no content length")
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

$SLEEP_CYCLE_SEC = 1

class RemoteControlHTTPProxyServer < HTTPProxyServer
	def proxy_service(req, res)
		if CONTROL_ERROR_STATUS != 0
			res.status = CONTROL_ERROR_STATUS
			res.body = ""
			puts("<TEST SERVER> return stauts code:" + res.status.to_s)
			return
		end
		if CONTROL_SLEEP_TIME != 0
			sleep_sec = CONTROL_SLEEP_TIME
			puts("<TEST SERVER> sleep " + sleep_sec.to_s + " (sec)...")
			while !:shutdown_called && sleep_sec > 0 do
				sleep($SLEEP_CYCLE_SEC)
				sleep_sec = sleep_sec - 1
				putc(".")
				STDOUT.flush
			end
			puts("<TEST SERVER> wake up!")
			return
		end
		super
	end
end

server = RemoteControlHTTPProxyServer.new({:BindAddress => $HOST_IP_ADDRESS,
							:Port => $LISTEN_PORT})
trap(:INT){
	shutdown_called = true
	server.shutdown
}


# return error statuc code
control_proc = Proc.new do |req, res|
	puts "req.path: " + req.path
	puts "req.query: " + req.query.to_s
	query = req.query
	if query["status"] != nil
		CONTROL_ERROR_STATUS = query["status"].to_i
		puts("<TEST SERVER> control status: " + query["status"])
	end
	if query["sleep"] != nil
		CONTROL_SLEEP_TIME = query["sleep"].to_i
		puts("<TEST SERVER> control sleep: " + query["sleep"])
	end
	if query["cl"] == "1" || query["cl"] == "on"
		CONTROL_NO_CONTENT_LENGTH = true
		puts("<TEST SERVER> control cl: " + query["cl"])
	elsif query["cl"] == "0" || query["cl"] == "off"
		CONTROL_NO_CONTENT_LENGTH = false
		puts("<TEST SERVER> control cl: " + query["cl"])
	end
	if query["sn"] == "1" || query["sn"] == "on"
		CONTROL_SLOW_NETWORK = true
		puts("<TEST SERVER> control sn: " + query["sn"])
	elsif query["sn"] == "0" || query["sn"] == "off"
		CONTROL_SLOW_NETWORK = false
		puts("<TEST SERVER> control sn: " + query["sn"])
	end
end
server.mount_proc('/control', control_proc)


server.start
