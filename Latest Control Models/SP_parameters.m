%% DAMPER/SPRING COEFFICENT IN MOTORS
LegSpring=50000;
LegDamp=1000;
%% LOAD EXTERNAL FORCE/TORQUE
load('Suran_23rd.mat');

%%%%
xForce=matlabStruct_Data.interface_r_on_socket_r_in_ground_fx;
zForce=(-1)*(matlabStruct_Data.interface_r_on_socket_r_in_ground_fy);
yForce=matlabStruct_Data.interface_r_on_socket_r_in_ground_fz;


resForce=[];
for i =1:length(xForce)
    resForce(i)=sqrt((xForce(i)*xForce(i))+(yForce(i)*yForce(i))+(zForce(i)*zForce(i)));
end

xTorque=matlabStruct_Data.interface_r_on_socket_r_in_ground_mx;
zTorque=matlabStruct_Data.interface_r_on_socket_r_in_ground_my;
yTorque=(-1)*(matlabStruct_Data.interface_r_on_socket_r_in_ground_mz);
resTorque=[];
for i =1:length(xTorque)
    resTorque(i)=sqrt((xTorque(i)*xTorque(i))+(yTorque(i)*yTorque(i))+(zTorque(i)*zTorque(i)));
end
Time=matlabStruct_Data.time;

%%%%
Time=0:1:87;
Time=0:2:174;
Time=0:5:(87*5);
Time=0:10:(87*10);
Time=Time';
%% PLOT FORCES
Forces = out.Forces.signals.values;
times = out.Forces.time;

force_1 = Forces(:,1);
plot(times, Forces(:,1), times, Forces(:,2), times, Forces(:,3), times, Forces(:,4), times, Forces(:,5), times, Forces(:,6))
legend('Leg 1', 'Leg 2', 'Leg 3', 'Leg 4', 'Leg 5', 'Leg 6')