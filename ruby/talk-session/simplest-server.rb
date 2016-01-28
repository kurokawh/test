#!/usr/bin/ruby
require "webrick"

httpd = WEBrick::HTTPServer.new(:DocumentRoot => File::dirname(__FILE__))
trap(:INT){ httpd.shutdown }
httpd.start
