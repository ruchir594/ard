function [direction, LR] = LeftRightReco(data,num_sc)

    Dth = 3;

//    data_pin = reshape(data,num_sc+1,length(data)/(num_sc+1))';
//    data_pin(:,14:end)=[];

    data_pin_diff = diff(data_pin); //data_pin of n, pin_diff of n-1
//    data_pin_diff(:,1) = [];
    data_direction = zeros(size(data_pin_diff)); // array of zeros

//    for m = 1:12
//        data_direction(find(data_pin_diff(:,m)<-Dth),m) = -1;
//        data_direction(find(data_pin_diff(:,m)>Dth),m) = 1;
//    end

    for m = 1:12
        data_f_start(m) = min(find(data_pin_diff(:,m)<-Dth));
//        data_f_end(m) = max(find(data_pin_diff(:,m)<-Dth));
//        data_r_start(m) = min(find(data_pin_diff(:,m)>Dth));
        data_r_end(m) = max(find(data_pin_diff(:,m)>Dth));
    end

    data_fall_start = sum(diff(data_f_start));
//    data_fall_end = sum(diff(data_f_end));
//    data_rise_start = sum(diff(data_r_start));
    data_rise_end = sum(diff(data_r_end));

    if (data_fall_start<0 || data_fall_end<0) && (data_rise_start<0 || data_rise_end<0)

        direction = 'right-to-left, sc12->sc1';
        LR = 0;

    elseif (data_fall_start>0 || data_fall_end>0) && (data_rise_start>0 || data_rise_end>0)

        direction = 'left-to-right, sc1->sc12';
        LR = 1;

    end

end
