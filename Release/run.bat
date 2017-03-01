ECHO OFF
REM chgfldt /D /F:.\test.txt
REM chgfldt /F:.\test.txt /CD:2017-01-02
REM chgfldt /F:.\test.txt /AD:2016-03-04
REM chgfldt /F:.\test.txt /MD:2015-05-06
REM chgfldt /F:.\test.txt /CT:07:08:09
REM chgfldt /F:.\test.txt /AT:10:11:12
REM chgfldt /F:.\test.txt /MT:13:14:15
REM chgfldt /F:.\test.txt /CD:9
REM chgfldt /F:.\test.txt /CD:2017-1-0
REM ECHO %ERRORLEVEL%
REM chgfldt /D /F:.\test.txt
ECHO ON
REM chgfldt /H

chgfldt /F:.\test.txt /CD:2007-11-12 /AD:2006-03-14 /MD:2005-05-16 /CT:17:18:19 /AT:20:21:22 /MT:03:04:05
