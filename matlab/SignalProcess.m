function [data_sp] = SignalProcess(data)

    zero_index = find(data==1023);
    data(1:zero_index(2)-1) = [];
    clear zero_index
    zero_index = find(data==1023);
    data(zero_index(end):end) = [];
    
    data_sp = data;

end