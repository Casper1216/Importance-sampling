clear ;close all;clc;
addpath('Count-4-cycles');
addpath('Count-6-cycles');
addpath('Count-8-cycles');
%addpath('Count-10-cycles');
A = textread('PEG_H.txt');
cn = A(4,1:A(1,2));
H = A(5+A(1,1):end,1:max(cn));
[num_4_cycles,vn_index_4] = count_4_cycles(H,cn);
[num_6_cycles,vn_index_6] = count_6_cycles(H,cn);
[num_8_cycles,vn_index_8] = count_8_cycles(H,cn);
fileID = fopen('6 cycle idex.txt','w');
fprintf(fileID,'%d %d %d\n',num_4_cycles,num_6_cycles,num_8_cycles);
% for i=1:num_4_cycles
%     for j=1:2
%         fprintf(fileID,'%d ',vn_index_4(i,j));
%     end
%     fprintf(fileID,'\n');
% end
for i=1:num_6_cycles
    for j=1:3
        fprintf(fileID,'%d ',vn_index_6(i,j));
    end
    fprintf(fileID,'\n');
end
% for i=1:num_8_cycles
%     for j=1:4
%         fprintf(fileID,'%d ',vn_index_8(i,j));
%     end
%     fprintf(fileID,'\n');
% end
