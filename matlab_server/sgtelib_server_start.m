function sgtelib_server_start(model,keepopen)

sgtelib_server_stop;
if nargin==1
    keepopen=false;
end

if nargin>=1
    model = ['\"' model '\"'];
else
    model = '';
end

disp('Launch sgtelib.exe in server mode.');

if keepopen
    %command = ['gnome-terminal -t sgtelib_server --hide-menubar -e "/bin/bash -c ''LD_LIBRARY_PATH=.; gdb -q -ex run --args sgtelib.exe -server -model ' model ' ; exec /bin/bash -i''" &'];
    command = ['gnome-terminal -t sgtelib_server --hide-menubar -e "/bin/bash -c ''LD_LIBRARY_PATH=.; gdb -q -ex run --args sgtelib.exe -verbose -server -model ' model ' ''"'];
else
    command = ['gnome-terminal -t sgtelib_server --hide-menubar -e "/bin/bash -c ''LD_LIBRARY_PATH=.; sgtelib.exe -server -model ' model ' ''"'];
end
disp(command)
[status,response] = system(command);
if keepopen
    pause(1);
end
if status || length(response)
    disp(command);
    status
    response
end
pause(0.5);