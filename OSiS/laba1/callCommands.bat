@ECHO OFF
(call createFolders.bat
call createFile.bat
call copyFile.cmd
call mergeFiles.bat %1 )>>%0.log