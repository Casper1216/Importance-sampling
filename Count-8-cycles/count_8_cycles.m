function [num_8_cycles,vn_index] = count_8_cycles(H, cn)
num_8_cycles_vec = zeros(3, 1);
vn_index_1 = [];
vn_index_2 = [];
vn_index_3 = [];
disp(' ');
disp('We are now counting the number of length-8-cycles in the target H.');
disp('Let us conut in parallel...This may take few seconds...')
for i_par = 1 : 12
    switch i_par
        case 1
            [num_8_cycles_vec(i_par),vn_index_1] = count_8_cycles_I(H, cn);
        case 2
            [num_8_cycles_vec(i_par),vn_index_2] = count_8_cycles_II(H, cn);
        case 3
            [num_8_cycles_vec(i_par),vn_index_3] = count_8_cycles_III(H, cn);
    end
end
vn_index = [vn_index_1;vn_index_2;vn_index_3];
num_8_cycles = sum(num_8_cycles_vec);
disp(' ');
disp(['The number of 8-cycles in the target H is ' num2str(num_8_cycles) '.'])
