gds = readtable('gds_n.csv');
id = readtable('id_n.csv');
vgs = readtable('vgs_n.csv');
gm = readtable('gm_n.csv');
gmoverid = readtable('gmoverid_n.csv');

gm = gm{1:end, 2:2:end};
id = id{1:end, 2:2:end};
gmoverid = gmoverid{1:end, 2:2:end};
gds = gds{1:end, 2:2:end};
vgs= vgs{1:end, 2:2:end};

gm_ro = gm./gds;
IDoverW = id/(1e-6);


Ls = {};
for i = 1:10
    Ls{i} = num2str(0.1*i);
end
Ls = Ls';

figure('name','VGS','color','white')
h = plot(gmoverid, vgs);    
set(h,{'DisplayName'},Ls);
title('NMOS');
xlabel('gm/id (S/A)');
ylabel('vgs (V)');
grid on;

figure('name','gm*ro','color','white')
h = plot(gmoverid, gm_ro);    
set(h,{'DisplayName'},Ls);
title('NMOS');
xlabel('gm/id (S/A)');
ylabel('gm*ro');
grid on;

figure('name','ID/W','color','white')
h = plot(gmoverid, IDoverW);    
set(h,{'DisplayName'},Ls);
title('NMOS');
xlabel('gm/id (S/A)');
ylabel('ID/W (uA/um)');
grid on;

