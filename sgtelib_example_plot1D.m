close all
clear all
clc
disp('=========== EXPLORER =============');

!cleanTerminals
! make -j 4
model = 'TYPE RBFI NB_NEIGHBORS 2 SHAPE_COEF 9999997 RIDGE 0.0010 KERNEL_TYPE I2'
model = 'TYPE RBF KERNEL_TYPE D1 PRESET XO'
%model = 'TYPE RBFS SHAPE_COEF -1 RIDGE -1 KERNEL_TYPE D1'
%model = 'TYPE LOWESS SHAPE_COEF 50 DEGREE 2 RIDGE 0.001 PRESET RGN'
% model = 'TYPE LOWESS SHAPE_COEF 10 DEGREE 2 RIDGE 0.0 PRESET D'
% model = 'TYPE LOWESS SHAPE_COEF 10 DEGREE 2 RIDGE 0.0 PRESET DEN'
% model = 'TYPE LOWESS SHAPE_COEF 10 DEGREE 2 RIDGE 0.0 PRESET DGN'
%model = 'TYPE ENSEMBLE WEIGHT OPTIM METRIC OECV'
%model = 'TYPE ENSEMBLE WEIGHT SELECT METRIC RMSECV'
%model = 'TYPE LOWESS SHAPE_COEF 20 DEGREE 2 RIDGE NO'
%model = 'TYPE RBFI SHAPE_COEF 5 RIDGE 0.0'
model = 'TYPE LOWESS SHAPE_COEF OPTIM KERNEL_TYPE OPTIM'
model = 'TYPE PRS DEGREE OPTIM RIDGE OPTIM'
model = 'TYPE ENSEMBLE PRESET SUPER1 WEIGHT OPTIM METRIC OECV'

%model = 'TYPE KRIGING METRIC OECV'


sgtelib_server_start(model,true)


disp('===========   START  =============');
sgtelib_server_ping;


P = 20;
X = sort(randn(P,1));


Z(:,1) = X.^2-X-3;
Z(:,2) = sign(X).*cos(X) + 5*randn(size(X));
Z(:,3) = mod(round(X),2)-0.5;
M = size(Z,2);


PP = 1000;
XX = sort([linspace(min(X)-1,max(X)+1,PP)' ; X]);

sgtelib_server_ping
sgtelib_server_newdata(X,Z);

figure;
hold on;
for i=1:M
    plot(X,Z(:,i),'o','color',get_color(i,M));
end



[ZZ,std,ei,cdf] = sgtelib_server_predict(XX);
disp('metrics...')
sgtelib_server_metric('RMSE')
sgtelib_server_metric('RMSECV')
sgtelib_server_metric('OECV')

for i=1:M
    plot(XX,ZZ(:,i),'-','color',get_color(i,M),'linewidth',2);
    plot(XX,ZZ(:,i)+std(:,i),'--','color',get_color(i,M));
    plot(XX,ZZ(:,i)-std(:,i),'--','color',get_color(i,M));
end

% plot(xlim,[0 0],'--k');
% disp('Get CV values');
% [Zh,Sh,Zv,Sv] = sgtelib_server_cv;
% for i=1:M
%     plot(X,Zv(:,i),'o','color',get_color(i,M));
%     for j=1:P
%         plot(X(j)*[1 1],Zv(j,i)+Sv(j,i)*[-1 +1],'-','color',get_color(i,M));
%     end
% end


disp('Plot EFI');
figure;
efi = ei(:,1).*prod(cdf(:,2:end),2);
efi = max(1e-16,efi);
plot(XX,efi,'g');
set(gca,'yscale','log')


