#!/usr/bin/ruby
#
# test_http_server.rb HOST_IP_ADDRESS LISTEN_PORT
# - HOST_IP_ADDRESS: if not set or "" or "-" is set, IP is obtained.
# - LISTEN_PORT: 80 is set by default
#
# http://HOST:PORT/error/XXX : status code XXX is returned.
# http://HOST:PORT/timeout/YYY: halt YYY (sec) without returnging response.

require 'webrick'


if ARGV[0] != nil && ARGV[0] != "" && ARGV[0] != "-"
	$HOST_IP_ADDRESS = ARGV[0]
else
	$HOST_IP_ADDRESS = IPSocket::getaddress(Socket::gethostname) #"127.0.0.1"
end
if ARGV[0] != nil
	$LISTEN_PORT = ARGV[1].to_i
else
	$LISTEN_PORT = 80
end


server = WEBrick::HTTPServer.new({:BindAddress => $HOST_IP_ADDRESS,
								  :Port => $LISTEN_PORT})

# parse path and return last part
# /a/b/c/d/1=> 1 (int)
def parse_path (path)
	basename = File::basename(path)
	return basename.to_i
end

DEFAULT_ERROR_STATUS = 503
# return error statuc code
error_proc = Proc.new do |req, res|
	res.status = parse_path(req.path)
	if res.status == 0
		res.status = DEFAULT_ERROR_STATUS
	end
	puts("<TEST SERVER> return stauts code:" + res.status.to_s)
end
server.mount_proc('/error', error_proc)


trap(:INT){
	server.shutdown
}
puts("")
puts("start server. available url:")
port_string = ""
if $LISTEN_PORT != 80
	port_string = ":" + $LISTEN_PORT.to_s
end
puts("  http://"+$HOST_IP_ADDRESS+port_string+"/error/XXX")
puts("signal ctrl-c to stop server.")
puts("")
server.start
