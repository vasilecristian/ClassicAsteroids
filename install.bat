@echo off

if not exist %~dp0Externals\DarkFunctionParser (
	svn co https://github.com/vasilecristian/DarkFunctionParser/trunk %~dp0Externals\DarkFunctionParser
) else (
	svn up %~dp0Externals\DarkFunctionParser
)

if not exist %~dp0Externals\TmxParser (
	svn co https://github.com/vasilecristian/TmxParser.git/trunk %~dp0Externals\TmxParser
) else (
	svn up %~dp0Externals\TmxParser
)

if not exist %~dp0Externals\tinyxml2 (
	svn co https://github.com/vasilecristian/tinyxml2.git/trunk %~dp0Externals\tinyxml2
) else (
	svn up %~dp0Externals\tinyxml2
)
