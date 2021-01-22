%% DAMPER/SPRING COEFFICENT IN MOTORS
LegSpring=50000;
LegDamp=1000;
%% LOAD EXTERNAL FORCE/TORQUE OLD
% load('FE.mat');
% 
% %%%%
% xForce=matlabStruct_Data.interface_r_on_socket_r_in_ground_fx;
% zForce=(-1)*(matlabStruct_Data.interface_r_on_socket_r_in_ground_fy);
% yForce=matlabStruct_Data.interface_r_on_socket_r_in_ground_fz;
% 
% 
% xTorque=matlabStruct_Data.interface_r_on_socket_r_in_ground_mx;
% zTorque=matlabStruct_Data.interface_r_on_socket_r_in_ground_my;
% yTorque=(-1)*(matlabStruct_Data.interface_r_on_socket_r_in_ground_mz);
% 
% Time=matlabStruct_Data.time;
% 
% %%%%
% Time=0:1:87;
% Time=0:2:174;
% Time=0:5:(87*5);
% Time=0:10:(87*10);
% Time=Time';
%% LOAD EXTERNAL FORCE/TORQUE NEW
load('Suran_23rd.mat');

%%%%
xForce=     matlabStruct_Data.socket_piston_x_force;
xForce([1:97,249:1200],:) = [];

yForce=(-1)*matlabStruct_Data.socket_piston_z_force;
yForce([1:97,249:1200],:) = [];

zForce=     matlabStruct_Data.socket_piston_y_force;
zForce([1:97,249:1200],:) = [];

xTorque=     matlabStruct_Data.socket_rotation_x_moment;
xTorque([1:97,249:1200],:) = [];

yTorque=(-1)*matlabStruct_Data.socket_rotation_z_moment;
yTorque([1:97,249:1200],:) = [];

zTorque=     matlabStruct_Data.socket_rotation_y_moment;
zTorque([1:97,249:1200],:) = [];

Time=matlabStruct_Data.time;
Time([1:97,247:1200],:) = [];
Time=Time-0.816664310;
TimeScale=150*2;

Time=0:2:TimeScale;
Time=Time';

%%
% Time=0:1:87;
% Time=0:2:174;
% Time=0:5:(87*5);
% Time=0:10:(87*10);
% Time=Time';
%% PLOT FORCES Run this after simulation
Forces = out.Forces.signals.values;
times = out.Forces.time;
save('Forces2Arduino.mat','Forces');
force_1 = Forces(:,1);
plot(times, Forces(:,1), times, Forces(:,2), times, Forces(:,3), times, Forces(:,4), times, Forces(:,5), times, Forces(:,6))
legend('Leg 1', 'Leg 2', 'Leg 3', 'Leg 4', 'Leg 5', 'Leg 6')