function sgtelib_server_start(model,keepopen)

sgtelib_server_stop;
if nargin==1
    keepopen=false;
end

% if nargin==0
%     model = '';
% end

if nargin>=1
    model = ['\"' model '\"'];
else
    model = '';
end

disp('Launch sgtelib_server.exe');

if keepopen
    command = ['gnome-terminal -t sgtelib_server --hide-menubar -e "/bin/bash -c ''LD_LIBRARY_PATH=.; gdb -ex run --args $SGTELIB_HOME/sgtelib_server.exe ' model ' ; exec /bin/bash -i''" &'];
else
    command = ['gnome-terminal -t sgtelib_server --hide-menubar -e "/bin/bash -c ''LD_LIBRARY_PATH=.; $SGTELIB_HOME/sgtelib_server.exe ' model ' ''"'];
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
