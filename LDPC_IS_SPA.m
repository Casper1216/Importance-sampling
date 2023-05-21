clear 
clc

%%


SPA = readmatrix("LDPC_SPA_96_48.csv");
IS = readmatrix("LDPC_IS_96_48.csv");





figure(1)
semilogy(SPA(1,:), SPA(3,:), 'b-pentagram');
hold on 
semilogy(SPA(1,:), SPA(2,:), 'r-O');
hold on 
semilogy(IS(1,:), IS(2,:), 'b-O');
hold on 


legend('FER-SPA','BER-SPA','FER-IS');
title('Performance');
xlabel('Eb/N0');
ylabel('error');