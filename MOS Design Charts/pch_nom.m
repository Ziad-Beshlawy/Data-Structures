gds = readtable('gds_p.csv');
id = readtable('id_p.csv');
vgs = readtable('vgs_p.csv');
gm = readtable('gm_p.csv');
gmoverid = readtable('gmoverid_p.csv');

gm = gm{1:end, 2:2:end};
id = abs(id{1:end, 2:2:end});
gmoverid = gmoverid{1:end, 2:2:end};
gds = gds{1:end, 2:2:end};
vgs= abs(vgs{1:end, 2:2:end});

gm_ro = gm./gds;
IDoverW = id/(1e-6);

Ls = {};
for i = 1:10
    Ls{i} = num2str(100*i);
end
Ls = Ls';

figure('name','VGS','color','white')
h = plot(gmoverid, vgs);    
set(h,{'DisplayName'},Ls);
title('PMOS');
xlabel('gm/id (S/A)');
ylabel('|vgs| (V)');
grid on;

figure('name','gm*ro','color','white')
h = plot(gmoverid, gm_ro);    
set(h,{'DisplayName'},Ls);
title('PMOS');
xlabel('gm/id (S/A)');
ylabel('gm*ro');
grid on;

figure('name','ID/W','color','white')
h = plot(gmoverid, IDoverW);    
set(h,{'DisplayName'},Ls);
title('PMOS');
xlabel('gm/id (S/A)');
ylabel('|ID/W| (uA/um)');
grid on;
