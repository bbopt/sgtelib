close all
clear all
clc
disp('=========== EXPLORER =============');

! make -j 4
model = 'TYPE CN'

sgtelib_server_start(model,true)


disp('===========   START  =============');
sgtelib_server_ping;


P = 8;
X = rand(P,1);
%load X_example.mat

f = @(X) 1+0.5*cos(6*X)+0.1*sin(20*X);
Z = f(X);


M = size(Z,2);


XX = (0:0.001:1)';
ZZreal = f(XX);


sgtelib_server_ping
sgtelib_server_newdata(X,Z);

figure('color','w');
hold on;
plot(X,Z,'o','color','k');


xlabel('$x$','interpreter','latex','fontsize',16)
ylabel('$y$','interpreter','latex','fontsize',16)

[ZZ,std,ei,cdf] = sgtelib_server_predict(XX);


plot(XX,ZZ,'r');

std = std/max(std);
plot(XX,ZZ+std,'--r');


ei = ei/max(ei);
plot(XX,ei,'k');


axis([0 1 0 2]);


legend('Data points','Surrogate model','Standard deviation')
set(legend,'location','north','fontsize',16)

plot(XX,ZZ-std,'--r');

export_fig('Example_Kriging.pdf','-pdf')



