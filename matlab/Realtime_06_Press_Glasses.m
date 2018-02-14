clear  
% clc  
close all

delete(instrfindall)

%% Setup Serial
s = serial('/dev/cu.usbmodem1431');  
s.BaudRate = 115200;  
s.DataBits = 8;  
s.Parity = 'none';
s.StopBits = 1;  
% s.Terminator = 0;  
s.InputBufferSize = 1024; 
s.OutputBufferSize = 1024;
% s.timeout = 20;  

tmax = 20;
num_sc = 12;
Dth = 0.5;
% Dth = [0.816814159292035,0.601501501501502,0.724624624624625,0.572560975609756,0.789552238805970,0.575609756097561,0.732530120481928,0.559214501510574,0.865217391304348,0.523312883435583,0.666765578635015,0.530722891566265];
dth = 0.1;

%% Setup Plot

data = 0;
time = 0;
count = 0;
index = [];
data_std = [];
data_min = [];
data_min_index = [];

% plotGraph1 = plot(time,data,'-r');
% hold on

%% Receive Data From Serial

fopen(s);

tic
while (toc <= tmax)
    if (fscanf(s,'%d') == 1023)

        for m = 1:num_sc
            data(m) = fscanf(s,'%d',256);
        end
//////////////////////
       setup  if mod(count,2000) == 1 && isempty(index) % maybe setup an index1 < 40 ?
            data_std = data;
            //data_min = data;
        end
        
%         //index = find((data_std - data)>20);
        if ~isempty(data_std)
            index = find((data./data_std)<Dth);
        end
/////////////////////////////
%         index = find(data<40);
        
        if ~isempty(data_min)
            data_min_index = find(data<data_min&data>0);
            if ~isempty(data_min_index)
                data_min(data_min_index) = data(data_min_index);
            end
            Dth = dth+data_min./data_std;
        end
        
        if ~isempty(index)
            x = [1:12];
            y = [6*ones(1,12)];
            plot(x,y,'ks','LineWidth',3,'MarkerSize',25)
            hold on
            grid on
            axis([0 13 0 12])
            
            index_up = index(find(index<=12));
            plot(index_up, 6*ones(1,length(index_up)),'ks','LineWidth',10,'MarkerSize',20)
                 
            hold off
        else
            x = [1:12];
            y = [6*ones(1,12)];
            plot(x,y,'ks','LineWidth',3,'MarkerSize',25)
            hold on
            grid on
            axis([0 13 0 12])
        end
            
        
        count = count+1;

        pause(0.001);
    end
end


fclose(s);
delete(s);
clear s

% data(cc)
% data_std(cc)
% ratio = data(cc)/data_std(cc)


