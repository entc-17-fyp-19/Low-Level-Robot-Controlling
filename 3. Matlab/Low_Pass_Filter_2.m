digits(5);
A_p = 0.5;
A_a = 10;
Op = 5;
Oa = 50;
Os = 100;
[a,N,oc] = kaiser(A_p,A_a,Op,Oa,Os);
Ioa = Io(a);
h_n = idealfilter(N,oc);

Wk_n = zeros(1,N);
for i = 1:N
    Wk_n(i) = window(a,i-1-(N-1)/2,N,Ioa);
end

hw_n = h_n.*Wk_n;

figure;
n = 1:N;
stem(n,hw_n);
xlabel('n');
ylabel('Amplitude');
title('Noncausal stopband filter window(Time domain)');

[Hw,f] = freqz(hw_n);%obtaining the frequency response and corresponding frequencies
w = f*Os/(2*pi);%Angular frequency
log_Hw = 20.*log10(abs(Hw));
figure;
plot(w,log_Hw);
xlabel('Angular frequency(rad/s)');
ylabel('Magnitude(dB)');
title('Magnitude response of the filter(Frequency domain)');

[X,n1] = inputsignal(600,oc,Os);

% Filtering using frequency domain multiplication
len_fft = length(X)+length(hw_n)-1; % length for fft in x dimension
x_fft = fft(X,len_fft);
hw_nT_fft = fft(hw_n,len_fft);
out_fft = hw_nT_fft.*x_fft;
out = ifft(out_fft,len_fft);
rec_out = out(floor(n/2)+1:length(out)-floor(n/2)); 

figure;
len_fft = 2^nextpow2(numel(n1))-1;
xfft_out = fft(rec_out,len_fft);
x_fft_out_plot = [abs([xfft_out(len_fft/2+1:len_fft)]),abs(xfft_out(1)),abs(xfft_out(2:len_fft/2+1))];
f = Os*linspace(0,1,len_fft)-Os/2;
plot(f,x_fft_out_plot);
xlabel('Frequency rad/s');
ylabel('Magnitude');
title('Output signal of the designed filter in the frequency domain'); 

output = zeros(1,numel(X)-N);
for i = 1:numel(X)-N
    output(i)= (X(i)*hw_n(1))+(X(i+1)*hw_n(2))+(X(i+2)*hw_n(3))+(X(i+3)*hw_n(4));
end 

figure;
len_fft = 2^nextpow2(numel(n1))-1;
xfft_out_2 = fft(output,len_fft);
x_fft_out_plot_2 = [abs([xfft_out_2(len_fft/2+1:len_fft)]),abs(xfft_out_2(1)),abs(xfft_out_2(2:len_fft/2+1))];
f = Os*linspace(0,1,len_fft)-Os/2;
plot(f,x_fft_out_plot_2);
xlabel('Frequency rad/s');
ylabel('Magnitude');
title('Output signal of the designed filter in the frequency domain 2'); 

function [a,N,oc] = kaiser(A_p,A_a,Op,Oa,Os)
op = (2*pi*Op)/Os;
oa = 2*pi*Oa/Os;
oc = (op+oa)/2;
d_p = vpa((10^(0.05*A_p)-1)/(10^(0.05*A_p)+1));
d_a = vpa(10^(-0.05*A_a));
d = min(d_a,d_p);
Aa = -20*log10(d);

if Aa <= 21 
    a = 0;
end
if (Aa > 21 & Aa <= 50)
    a = 0.5842*((Aa-21)^0.4) + 0.07886*(Aa-21);
end
if Aa > 50
    a = 0.1102*(Aa-8.7);
end

if Aa <= 21 
    D = 0.9222;
end
if Aa > 21
    D = (Aa-7.95)/14.36;
end

N = double(ceil(((2*pi*D)/(oa-op))+1));
end

function Iox = Io(x)
Iox = 1;
for k = 1:100
    Iox = Iox + ((1/factorial(k))* (x/2)^k)^2;
end
end

function Wk = window(a,n,N,Ioa)
B = a*(1-((2*n)/(N-1))^2)^0.5;
IoB = Io(B);
Wk = IoB/Ioa;
end

function h_n = idealfilter(N,oc)
h_n = zeros(1,N);
for i = 1:N
    if i == 1+((N-1)/2)
        h_n(i)= oc/pi;
    else
        n = i-1-(N-1)/2;
        h_n(i)= sin(oc*n)/(pi*n);
    end
end
end

function [X,n1] = inputsignal(samples,oc,Os)
%Component frequencies of the input
O1 = oc/2;
O2 = O1 + oc;
%Generating the discrete signal
n1 = 0:1:samples;
X = cos(O1.*n1)+cos(O2.*n1);
figure;
subplot(2,1,1);
stem(n1,X);
xlabel('n');
ylabel('Amplitude');
title('Input signal(Time domain)')
subplot(2,1,2);
len_fft = 2^nextpow2(numel(n1))-1;
x_fft = fft(X,len_fft);
x_fft_plot = [abs([x_fft(len_fft/2+1:len_fft)]),abs(x_fft(1)),abs(x_fft(2:len_fft/2+1))];
f = Os*linspace(0,1,len_fft)-Os/2;
plot(f,x_fft_plot);
xlabel('Frequency rad/s');
ylabel('Magnitude');
title('Input signal in the frequency domain');
axis tight;
end



