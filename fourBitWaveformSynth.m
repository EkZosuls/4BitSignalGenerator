% Make a synthesized signal for microcontroller playback into a
% simple 4 bit parallel DAC. Let the playback device set the sample rate.
% This is sample rate agnostic.
% Copyright 2021 Aleks Zosuls


ptsPerCycle = 8; %specify points per cycle. Repeat cycles on playback to
% get tone bursts
%set the frequencies and amplitudes. Note we can violate Nyquist here if our harmonics are high. 
A1 = 1;
F1 = 110;
A2 = .5;
F2 = 2* F1;
A3 = .5;
F3 = 3* F1;
%Generate the time base
T = (0:ptsPerCycle-1)./(ptsPerCycle*F1);
%T = (0:100-1)./(ptsPerCycle*F1);
%calculate discrete sine values
s1 = A1* sin(2*pi*F1*T);
s2 = A2* sin(2*pi*F2*T);
s3 = A3* sin(2*pi*F3*T);

supahhPos = s1+s2+s3; % sum the three sinusoids
spNorm = supahhPos/max(supahhPos); % normalize ampitudes to 1
spShift = 15* (0.5*spNorm + 0.5); %scale and shift for binary representation
quantz = round(spShift);    % quantize to integers for LUT
figure
plot(T,quantz)      % check our maths.


%%
% make the figure for the lab doc
figure
ptsPerCycle = 16
TB = (0:3*ptsPerCycle-1)./(ptsPerCycle*F1); % three cyclz
s1r = A1* sin(2*pi*F1*TB);
s2r = A2* sin(2*pi*F2*TB);
s3r = A3* sin(2*pi*F2*2*TB);
subplot(2,4,1)
plot(TB,s1r)
axis([-.005,.0305,-1.3, 1.3])
subplot(2,4,2)
plot(TB, s2r)
axis([-.005,.0305,-1.3, 1.3])
subplot(2,4,3)
plot(TB, s3r)
axis([-.005,.0305,-1.3, 1.3])
subplot(2,4,4)
plot(TB, s1r+s2r+s3r)
axis([-.005,.0305,-1.3, 1.3])

subplot(2,4,5)
stem(F1, A1)
axis([0,500,0, 1.3])
subplot(2,4,6)
stem(F2,A2)
axis([0,500,0, 1.3])
subplot(2,4,7)
stem(F2*2, A3)
axis([0,500,0, 1.3])
subplot(2,4,8)
stem([F1 F2 F2*2],[A1 A2 A3])
axis([0,500,0, 1.3])

