@echo off

java -Xmx900m -XX:MaxPermSize=256m -XX:ReservedCodeCacheSize=256m -client -jar third_party\jruby\jruby-complete.jar -X-C -S rake %*
