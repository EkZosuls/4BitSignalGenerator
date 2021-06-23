% Make a simple synthesized signal for microcontroller playback into a
% simple 4 bit parallel DAC.
% Copyright 2021 Aleks Zosuls

%sampleRate = 2000;
ptsPerCycle = 8;
A1 = 1;
F1 = 110;
A2 = .5;
F2 = 2* F1;
A3 = .5;
F3 = 3* F1;
T = (0:ptsPerCycle-1)./(ptsPerCycle*F1);
%T = (0:100-1)./(ptsPerCycle*F1);
s1 = A1* sin(2*pi*F1*T);
s2 = A2* sin(2*pi*F2*T);
s3 = A3* sin(2*pi*F3*T);

supahhPos = s1+s2+s3;
spNorm = supahhPos/max(supahhPos);
spShift = 15* (0.5*spNorm + 0.5);
quantz = round(spShift);
figure
plot(T,quantz)


%%


%use quantizer to make four bit version
%q = quantizer('mode', 'ufixed', 'overflowmode', 'saturate', 'format', [5 4]);
%output2 = quantize(q, spShift);