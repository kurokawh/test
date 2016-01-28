#!/usr/bin/ruby

require 'net/http'
require 'uri'

if (ARGV.size == 0) 
	puts ""
	puts "ERROR: No url is given."
	puts "e.g.:> ruby head.rb http://host.name:port/path/a/b.html"
	puts ""
	exit
end

uri = URI.parse(ARGV[0])
http = Net::HTTP.new(uri.host, uri.port)
#response = http.head(uri.path)
response = http.get(uri.path + "?" + uri.query)


# レスポンスオブジェクトを表示
puts "<<response>>"
p response

# コード部分(status lineに含まれる数値)を表示
puts "<<response.code>>"
p response.code

# 各HTTPヘッダの名前と値を表示
puts "<<response.header>>"
response.each do |name,value|
  puts name + " : " + value + "\n"
end
puts "\n"

if (ARGV.size >= 2 && ARGV[1] == "body") 
	puts "================== <<response.body>> =================="
	puts response.body
	puts "\n"
end
