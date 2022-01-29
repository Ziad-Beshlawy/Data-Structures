% Initalization
noise = n4;
set_size = length(noise);

% Stage 1
% performs a sweep across the whole set using a fixed length window 
% the goal is to find the period and the approximate location 
% to be used in stage 2

window_length = 360;
maxs = zeros(1, set_size - window_length);
frequencies = zeros(1, set_size - window_length);
variance = zeros(1, set_size - window_length);
for s = 1:(set_size - window_length)
    e = s + window_length - 1;
    c = conv(noise(s:e), flip(noise(s:e))); % equivalent to autocorr()
    freq_response = abs((1/(s-e))*fft(c));
    [maxs(s), frequencies(s)] = max(freq_response);
    variance(s) = var(freq_response);
end

figure('name','max vs s');
stem(maxs, 'marker', 'none');
title('max vs starting point');
ylabel('max');
xlabel('s');

figure('name','frequencies vs s');
stem(frequencies, 'marker', 'none');
title('frequency vs starting point');
ylabel('index(frequency)');
xlabel('s');

figure('name','variances vs s');
stem(variance, 'marker', 'none');
title('variance vs starting point');
ylabel('variance');
xlabel('s');

[m, k] = max(maxs);
N = (2*window_length)/(frequencies(k)-1)

max_variance = max(variance);
range = find(variance > 0.05*max_variance);

% stage 2
% performs a sweep across 'range' using a variable size window

A = 0;
S = 1;
L = 10;
for l = N:N:(range(end)-range(1))
    for s = range
        c = conv(noise(s:s+l-1), flip(noise(s:s+l-1)));
        freq_response_c = (1/l)*fft(c);
        magnitude_c = abs(freq_response_c);
        %a = max(magnitude_c(1:l));
        a = var(magnitude_c(1:l));
        if a > A 
            A = a;
            S = s;
            L = l;
        end
    end
end

S = S
L = L


freq_resp = (1/L)*abs(fft(noise(S:S+L-1)));
figure('name','range');
stem(0:L-1,freq_resp,'marker','none');
title('fft() at the location of the signal');
A = 2*max(freq_resp)
