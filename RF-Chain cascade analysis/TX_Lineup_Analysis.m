% inputs: #block_name = [Gain(dB) NF(dB) IIP3(dBm)] 
Phase_Shifter =[-5.5 5.5 25.5];
Attenuator_1 = [-4 4 24];
Switch_1 = [-1.5 1.5 41.5];
Attenuator_2 = [-4 4 24];
Amplifier = [22.5 4 -3.5];
PA = [20 7 7];
Switch_2 = [-1.5 1.5 41.5];

N =7;

att1_gains = [(Attenuator_1(1)-15)*ones(5,1); (linspace(Attenuator_1(1)-14,Attenuator_1(1),15))' ;Attenuator_1(1)*ones(40,1)];
att2_gains = [(Attenuator_2(1)-15)*ones(20,1); (linspace(Attenuator_2(1)-14,Attenuator_2(1),15))' ;Attenuator_2(1)*ones(25,1)];
att1_NFs = [(Attenuator_1(2)+15)*ones(5,1); (linspace(Attenuator_1(2)+14,Attenuator_1(2),15))' ;Attenuator_1(2)*ones(40,1)];
att2_NFs = [(Attenuator_2(2)+15)*ones(20,1); (linspace(Attenuator_2(2)+14,Attenuator_2(2),15))' ;Attenuator_2(2)*ones(25,1)];
%att1_IIP3s = [Attenuator_1(1)*ones(45,1); (linspace(Attenuator_1(1)+3,Attenuator_1(1)+45,15))' ;(Attenuator_1(1)+45)*ones(40,1)];
%att2_IIP3s = [Attenuator_2(1)*ones(60,1); (linspace(Attenuator_2(1)+3,Attenuator_2(1)+45,15))' ;(Attenuator_2(1)+45)*ones(25,1)];


% using friis equation to calcuate chain OIP3 and total NF:
Gains_dB = [
    Phase_Shifter(1)*ones(60,1)...
    att1_gains...
    Switch_1(1)*ones(60,1) ...
    att2_gains ...
    Amplifier(1)*ones(60,1) ...
    PA(1)*ones(60,1) ...
    Switch_2(1)*ones(60,1) ...
    ];
NFs_dB = [
    Phase_Shifter(2)*ones(60,1)...
    att1_NFs...
    Switch_1(2)*ones(60,1) ...
    att2_NFs ...
    Amplifier(2)*ones(60,1) ...
    PA(2)*ones(60,1) ...
    Switch_2(2)*ones(60,1) ...
    ];
IIP3s_dBm = [
    Phase_Shifter(3)*ones(60,1)...
    Attenuator_1(3)*ones(60,1)...
    Switch_1(3)*ones(60,1) ...
    Attenuator_2(3)*ones(60,1) ...
    Amplifier(3)*ones(60,1) ...
    PA(3)*ones(60,1) ...
    Switch_2(3)*ones(60,1) ...
    ];

Gains = 10.^(Gains_dB/10);
NFs = 10.^(NFs_dB/10);
IIP3s = 10.^(IIP3s_dBm/10);

Cumlative_Gains = [ones(60,1) cumprod(Gains(:,1:N-1), 2)]; %[g1 g1g2 g1g2g3 ...]
NF_contributions = (NFs - [zeros(60,1) ones(60,N-1)])./Cumlative_Gains;

IIP3_contributions = Cumlative_Gains./(IIP3s);
total_IIP3_dB = 10*log10(1./sum(IIP3_contributions,2));

total_NF_dB = 10*log10(sum(NF_contributions,2));

% calculating SNR, SDR, and SNDR for a given channel BW:

BW = 800e6;
Po = -30:1:29; % in dBm

total_gain_dB = sum(Gains_dB, 2);
SNR_o_dB = Po-total_NF_dB'+174-10*log10(BW)-total_gain_dB';
total_OIP3_dB = total_gain_dB+total_IIP3_dB;
SDR_dB = 2*(total_OIP3_dB'-Po);
SNR_o = 10.^(SNR_o_dB/10);
SDR = 10.^(SDR_dB/10);

SNDR = (SNR_o.*SDR)./(SNR_o+SDR);
SNDR_dB = 10*log10(SNDR);

figure();
plot(Po, SNR_o_dB);
hold on;
plot(Po,SDR_dB);
plot(Po, SNDR_dB);
hold off;

title('SNDR of TX @Pin=-15dBm BW=800MHz');
xlabel('Po(dBm)');

