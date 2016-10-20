close all
clear all
clc
disp('====== TEST SGTELIB_START for ROBIN ==========');


model = 'TYPE PRS DEGREE 2 RIDGE 0.01'

sgtelib_exe = '/home/bastien/NOMAD_SGTELIB_013_RBFI_and_options/sgtelib/sgtelib_server.exe';

!killName sgtelib_server.exe
% Just a dummy command
cmd1 = 'pwd'
% Something needed on my computer. 
% If you don't need it, just put 'ls' or 'pwd' instead.
cmd2 = 'LD_LIBRARY_PATH=.'
% Start sgtelib
cmd3 = [sgtelib_exe ' ' model]
% Keep it open (maybe not necessary). If not needed, replace by 'ls'. 
cmd4 = 'exec /bin/bash -i'


command = ['xterm -hold -e '' ' cmd1 ' ; ' cmd2 ' ; ' cmd3 ' ; ' cmd4 ' '' &'];

system(command)


