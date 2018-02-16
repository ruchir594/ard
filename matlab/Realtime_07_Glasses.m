clear  
clc  
close all

delete(instrfindall)

%% Setup Serial
s = serial('/dev/cu.usbmodem1431');  
s.BaudRate = 115200;  
s.DataBits = 8;  
s.Parity = 'none';  
s.StopBits = 1;  
% Serial_obj.Terminator = 0;  
s.InputBufferSize = 1024; 
s.OutputBufferSize = 1024; 
% Serial_obj.timeout = 20;  

tmax = 2;
num_sc = 12;

%% Receive Data From Serial
data = [];

fopen(s);
% data = fscanf(Serial_obj,'%d',10);

tic
while toc <= tmax
    data = [data, double(fscanf(s,'%d',256))];
end

toc

fclose(s);
delete(s);
clear s

data_sp = SignalProcess(data);
[direction, LR] = LeftRightReco(data_sp, num_sc);
direction


x = [1:12, 12*ones(1,11), 12:-1:1, ones(1,11)];
y = [ones(1,12), 1:11, 11*ones(1,12), 11:-1:1];
plot(x,y,'ks','LineWidth',3,'MarkerSize',25)
hold on
grid on
axis([0 13 0 12])

if LR == 1
    quiver(1,6,12,0)
elseif LR == 0
    quiver(12,6,-12,0)
end




