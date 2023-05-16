function [num_4_cycles,vn_index] = count_4_cycles(H, cn)
disp('We are now counting the number of length-4-cycles in the target H.');
vn_index = [];
M = size(H, 1);
num_4_cycles = 0;
for x1 = 1 : M-1
    for n1 = 1:cn(x1)
        y1 = H(x1,n1);
        for n2 = n1+1:cn(x1)
            y2 = H(x1,n2);
            for x2 = x1+1:M
                for n2 = 1:cn(x2)
                    if(H(x2,n2)==y2)
                        for n3 = 1:n2
                            if(H(x2,n3)==y1)
                                num_4_cycles = num_4_cycles + 1;
                                vn_index = [vn_index;y1,y2];
                            end
                        end
                    end
                end
            end
        end
    end
end
disp(' ');
disp(['The number of 4-cycles in the target H is ' num2str(num_4_cycles) '.'])