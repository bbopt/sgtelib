close all
clear all
clc

% Read the data in help_data.tex and convert them to build
% the file sgtelib_help.cpp



COMMANDS = {'\kwa','\kwb','\kwc'};
NC = length(COMMANDS);
findcmd = false(NC,1);
DATA = cell(0,NC);

str = '';
ci = 1;
cj = 0;


file = 'help_data.tex';
fid = fopen(file);
while true
    line = fgetl(fid);
    if ~ischar(line)
        break;
    end

    disp(line);
    % Clean the line
    line = cleanSpaces(line);

    if isempty(line) || line(1)=='%'
        continue;
    end

    % Find which command(s) are in the line
    for i=1:NC
        findcmd(i) = ~isempty(strfind(line,COMMANDS{i}));
    end
    % Error if more than one command.
    if sum(findcmd)>1
        disp(line);
        error('Several commands in this line!');
    end
    % If there is exactly one command
    if sum(findcmd)==1
        % Update the index of the command.
        disp('===================');
        ci = find(findcmd)
        if ci==1
            cj = cj+1;
        end
        cj
        % Open new string in DATA
        DATA{cj,ci} = '';

        % Remove the command from the line
        line = strrep(line,COMMANDS{ci},'');
    end

    DATA{cj,ci} = [DATA{cj,ci} line];

end
fclose(fid);

REPLACES = { 
    '\newline','\n'
    '\linebreak','\n'
    '\\','\n'
    '\item','\n  * '
    '\begin{itemize}',''
    '\end{itemize}','\n'
    '\quote{{\tt ',''
    '{\tt ',''
    '}',''
    '"','\"'
    '\myUnderline{',''
    '\textbf{',''
    '\textbf{',''
    '\_','_'
    '{',''
    '}',''
    '$',''
    '\n','SPECIALKWNEWLINE'
    '\"','SPECIALKWQUOTE'
    '\',''
    'SPECIALKWNEWLINE','\n'
    'SPECIALKWQUOTE','\"'
    };

for cj=1:size(DATA,1)
    for ci=1:NC
        % Clean string
        str = cleanSpaces(DATA{cj,ci});
        % Remove brackets.
        if str(1) == '{'
            str(1) = [];
        else
            disp(str);
            error('Does not start with curbe bracket');
        end
        if str(end) == '}'
            str(end) = [];
        else
            disp(str);
            error('Does not end with curbe bracket');
        end

        % Clean string again
        str = cleanSpaces(str);
        % Other cleaning
        for k=1:size(REPLACES,1)
            str = strrep(str,REPLACES{k,1},REPLACES{k,2});
        end
        while length(str)>=2 && strcmp(str(1:2),'\n')
            str(1:2) = [];
        end
        while length(str)>=2 && strcmp(str(end-1:end),'\n')
            str(end-1:end) = [];
        end
        str = strrep(str,'\n',['\n"' char(10) '"'])
        % Other modifications
        DATA{cj,ci} = str;
    end
end

NL = size(DATA,1);
for i=1:NL
    for j=1:NC
        disp([num2str(i) ',' num2str(j) '==' DATA{i,j} '==']);
    end
end


% Write cpp file.
file = '../src/sgtelib_help.cpp';

copyfile('help_header.cpp',file);

fid = fopen(file,'a');
newline = char(10);
mywrite = @(line) fwrite(fid,[line newline]);


mywrite('//================================');
mywrite('//  Get dimension of HELP_DATA');
mywrite('//================================');
mywrite('int SGTELIB::dim_help_data (void){');
mywrite(['  return ' num2str(NL) ';']);
mywrite('}//');
mywrite('');
mywrite('//================================');
mywrite('//  Construct the help data');
mywrite('//================================');
mywrite('std::string ** SGTELIB::get_help_data (void){');
mywrite = @(line) fwrite(fid,['  ' line newline]);
mywrite('int i;');
mywrite(['const int NL = ' num2str(NL) ';']);
mywrite(['const int NC = ' num2str(NC) ';']);
mywrite('std::string ** HELP_DATA = new std::string * [NL];');
mywrite('for (i = 0 ; i<NL ; i++) HELP_DATA[i] = new std::string [NC];');

for i=1:NL
    mywrite(['//================================']);
    mywrite(['//      ' DATA{i,1}]);
    mywrite(['//================================']);
    mywrite(['i = ' num2str(i-1) ';']);
    for j=1:NC
        mywrite(['HELP_DATA[i][' num2str(j-1) '] = "' DATA{i,j} '";']);

    end
end

mywrite(['//================================']);
mywrite('return HELP_DATA;');

mywrite = @(line) fwrite(fid,[line newline]);
mywrite('}//');

fclose(fid);
edit(file);


