@for /f "delims=" %%a in ('c:\msys64\usr\bin\cygpath %cd%') do @set proj_path=%%a
c:\msys64\usr\bin\bash.exe -c %proj_path%/build.sh %1 %2 %3 %4 %5
