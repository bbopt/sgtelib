close all
clear all
clc
disp('=========== EXPLORER =============');
!cleanTerminals
! make -j 4

model = 'TYPE PRS DEGREE 2 RIDGE 0.01'
%model = 'TYPE RBF DISTANCE_TYPE NORM2_IS0 KERNEL_COEF 2 KERNEL_TYPE D2'
model = 'TYPE KS DISTANCE_TYPE NORM2_IS0 KERNEL_COEF 1000 KERNEL_TYPE D1'
%model = 'TYPE ENSEMBLE WEIGHT SELECT METRIC RMSECV'
%model = 'TYPE ENSEMBLE WEIGHT OPTIM METRIC LINV PRESET IS0'
model = 'TYPE ENSEMBLE WEIGHT OPTIM METRIC ARMSECV PRESET SUPER1'
model = 'TYPE RBF PRESET O KERNEL_TYPE D1'
model = 'TYPE KRIGING METRIC LINV'
%model = 'TYPE ENSEMBLE WEIGHT SELECT METRIC OECV PRESET DEFAULT'


sgtelib_server_start(model,true)
sgtelib_server_ping;

N = 2;
PP1 = 25;
PP2 = 20;
scale_x1 = 0:PP1-1;
scale_x2 = 0:PP2-1;
[x1,x2] = meshgrid( scale_x1 , scale_x2 );
XX = [x1(:) x2(:)];
PP = (PP1)*(PP2);



P = 20;


X = XX(randperm(PP),:);
X = X(1:P,:);

f = @(x) cos(sqrt(0.5*x(:,1))).*cos(0.1*x(:,2));
Z = f(X);

Z = Z + 0.05*randn(size(Z));

sgtelib_server_newdata(X,Z);

tic
[ZZ,std,ei,cdf] = sgtelib_server_predict(XX);
toc
if max(abs(ZZ))<1e+6

    figure
    subplot(2,2,1);hold on;
    plot3(X(:,1),X(:,2),Z,'k.');
    surf(x1,x2,reshape(f(XX),PP2,PP1));
    set(gca,'view',[-37.5000   30.0000]);
    set(gca,'ydir','normal')
    xlabel('Real Z');
    zlim([-2 +2]);

    subplot(2,2,2);hold on;
    plot3(X(:,1),X(:,2),Z,'k.');
    surf(x1,x2,reshape(ZZ,PP2,PP1));
    set(gca,'view',[-37.5000   30.0000]);
    xlabel('Zh');
    zlim([-2 +2]);

    subplot(2,2,3);hold on;
    imagesc(scale_x1,scale_x2,reshape(f(XX),PP2,PP1));
    set(gca,'ydir','normal');
    plot(X(:,1),X(:,2),'k.');
    axis([-0.5 PP1-0.5 -0.5 PP2-0.5])

    subplot(2,2,4);hold on;
    imagesc(scale_x1,scale_x2,reshape(ZZ,PP2,PP1));
    set(gca,'ydir','normal');
    plot(X(:,1),X(:,2),'k.');
    axis([-0.5 PP1-0.5 -0.5 PP2-0.5]) 

else
    disp(ZZ)
    
end

disp('metric:')
sgtelib_server_metric('AOECV')

%sgtelib_server_stop;
