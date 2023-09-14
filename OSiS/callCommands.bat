@ECHO OFF
(call createFolders.bat
call createFile.bat
call copyFile.cmd
call mergeFiles.bat KOLYA )>>%0.log