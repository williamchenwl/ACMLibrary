:loop 
 datamaker>1.in
 bl.exe<1.in>1.out
 std.exe<1.in>2.out
 fc 1.out 2.out
 if errorlevel 1 goto end
 pause
end