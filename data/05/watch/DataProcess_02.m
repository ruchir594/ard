clear all

data = load('raw_12_0_unsync.txt');
alfa = 0.7;

% data_pin = reshape(data,16+1,length(data)/(12+1))';
data_pin = data;
data_pin(:,1) = [];

data_diff = diff(data_pin);

% for m = 1:149
%   
%     if min(data_diff(m,:))<-400
%         index = find(data_diff(m,:) == min(data_diff(m,:)))
%         t = m
%     end
% 
% end

% figure
plot(data_pin)

data_m = data_pin;
data_me = median(data_m);
for a = 1:size(data_m,1)
    for b = 1:16
        if data_m(a,b) > 0.8* data_me(b)
            data_m(a,b) = data_me(b);
        end
    end
end

% m = 1;
% a = 1;
% cnt = 0;

% while 1
%     
%     if ~isempty(find(data_m(a,:)<alfa*median(data_m(a,:))))
%         index1 = find(data_m(a,:) == min(data_m(a,:)));
%         if ~isempty(find(data_m(a+1,:)<alfa*median(data_m(a+1,:))))
%             index2 = find(data_m(a+1,:) == min(data_m(a+1,:)));
%             if index2 < index1
%                 cnt = cnt + 1;
%             elseif index2 > index1
%                 DD(m) = -1;
%                 m = m+1;
%             elseif index2 == index1
%                 DD(m) = 0;
%                 m = m+1;
%             end       
%         end
%         
%         
%     else
%         a = a+1;
%     end
%     
%     if a == size(data_m,1)
%         break;
%     end
%     
%     
% end

% data_m = data_pin;

a = 1;
m = 1;
index = [];
cnt = 0;
cnt_frame = [];
n = 1;

while 1
    
    if ~isempty(find(data_m(a,:) < alfa*median(data_m(a,:))))   % alfa*median(data_m(a,:))
        index(m) = floor(mean(find(data_m(a,:) == min(data_m(a,:)))));
        frame(m) = a;
        m = m + 1;
    else
        
        if ~isempty(index)
            pp = index;
            ppp = frame;
            index = [];
            frame = [];
        end
                    
        
        if m > 10
            cnt = cnt+1;
            
            if sum(diff(pp))<0
                DD(cnt) = 1;
            elseif sum(diff(pp))>0
                DD(cnt) = -1;
                pp
                ppp
            else
                DD(cnt) = 0;
            end
            
            cnt_frame(n) = a;
            n = n+1;
        end
        m = 1;
        
    end    
    
        
    
    if a == size(data_m,1)
        break;
    end
    a = a+1;
    
end
        












