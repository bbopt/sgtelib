%% Sgtelib_predict Build for Matlab

% To recompile you will need to get / do the following:

% 1) Get SGTELIB
% SGTELIB is available from https://github.com/bastientalgorn/sgtelib
% Define the $SGTELIB_HOME environment variable to the path where SGTELIB
% was downloaded and extracted.
%
% 2) Start Matlab and go into $SGTELIB_HOME/matlab_mex
%
% 3) Compile the MEX File by executing this file in Matlab
%
% The code below will build the sgtelib_predict MEX file and set the Matlab path.


% Check and set sgtelib_home and create variables for path
clear sgtelib_home sgtelib_src sgtelib_bin ;

sgtelib_home = getenv('SGTELIB_HOME');

% Current directory
cdir = cd;

if ( length(sgtelib_home) > 1)
    warning('The sgtelib_home variable for Matlab is set to %s. The default can be replaced by using the command setenv(''SGTELIB_HOME'',ARG1)! before running the build_sgtelib_predict.m script.',sgtelib_home);
    if ( ~isempty( find(isspace(sgtelib_home),1) ) )
        error('The compilation of sgtelib_predict for Matlab must be performed in the matlab_mex directory. The path should not contain empty space.');
    end
else
    cd ..
    sgtelib_home = cd; 
    if ( ~ exist(sgtelib_home,'dir') )
            error('The default sgtelib directory does not exist. Please set the SGTELIB_HOME variable using the command setenv(''SGTELIB_HOME'',ARG1)! before running the build_sgtelib_predict.m script.');
    end
    cd (cdir);
    
end
  
sgtelib_src=[sgtelib_home filesep 'src' filesep];
sgtelib_bin=[sgtelib_home filesep 'bin' filesep];

post = [' -I.  -I' sgtelib_src ' -lut -output ' sgtelib_bin filesep 'sgtelib_predict.' mexext];
pre = ['mex -v -largeArrayDims sgtelib_predict_mex.cpp ' sgtelib_src 'Kernel.cpp ' sgtelib_src 'Surrogate_Ensemble.cpp ' sgtelib_src 'Surrogate_LOWESS.cpp	'...
sgtelib_src 'Surrogate_Parameters.cpp	' sgtelib_src 'TrainingSet.cpp ' sgtelib_src 'Matrix.cpp '...
sgtelib_src 'Surrogate_Factory.cpp ' sgtelib_src 'Surrogate_PRS.cpp ' sgtelib_src 'Surrogate_RBF.cpp '...
sgtelib_src 'sgtelib.cpp ' sgtelib_src 'Surrogate.cpp ' sgtelib_src 'Surrogate_KS.cpp ' sgtelib_src 'Surrogate_PRS_CAT.cpp '...
sgtelib_src 'Surrogate_Utils.cpp ' sgtelib_src 'sgtelib_help.cpp '  sgtelib_src 'Surrogate_CN.cpp ' ...
sgtelib_src 'Surrogate_Kriging.cpp '  sgtelib_src 'Surrogate_PRS_EDGE.cpp ' sgtelib_src 'Tests.cpp ' ];


fprintf('\n-------------------------------\n');
fprintf('SGTELIB_PREDIC MEX FILE BUILD \n\n');


try

    eval([pre post])

    fprintf('Compilation done!\n');
    fprintf('\n----------------------------------------------------------------------------------------------\n');
    fprintf(' To be able to use the sgtelib_predict function, you may need to modify the Matlab path \n');
    qstring = 'To be able to use the sgtelib_predict function, you may need to modify the Matlab path. Do you want to update the Matlab path?';
    choice = questdlg(qstring,'Set path','Yes','No','Yes');
    if ( strcmp(choice,'Yes') )
        addpath(sgtelib_bin);
        fprintf('  ---> The path has been modified but not saved.\n');
    end
    cd (cdir)
    clear cdir sgtelib_home sgtelib_bin sgtelib_src post pre choice ;
    
catch ME
    cd (cdir)
	clear sgtelib_home sgtelib_bin sgtelib_src cdir post pre choice ;
    error('Error Compiling sgtelib_predict !\n%s',ME.message);
end
