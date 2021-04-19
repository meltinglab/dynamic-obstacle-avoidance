%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script built to make a comparison between kinematic and       %
% linearized vehicle model with dynamic non linear vehicle      %
% model.                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all
close all
clc
%% Include useful folders
addpath('./Scripts');
addpath('./Files');
addpath('./SimulinkModels');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% PARAMETERS FOR DYNAMIC MODEL  %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

param = loadParameters(1);       % Load vehicle parameters
V= 20/3.6;                       % [m/s] Vehicle speed

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% SIMULATION SETUP %%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ts = 0.001;                              % [s] Sampling time
T_fin = 10;                              % [s] Duration of simulation
T_in = linspace(0,T_fin,1000)';          % Input time vector
x0_dyn = [0; 0; 0; V; 0; 0];             % Initial condition for dynamic model
x0_kin = [0; 0; 0; V];                    % Initial condition for kinematic model
param_test = [[0;T_fin] [param';param']]; % Parameters of vehicle

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% TEST CASES DEFINITION %%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 1) Free Evolution (NO Input)
Throttle_in = zeros(length(T_in),1);      % [m/s^2] Throttle
Delta_in = zeros(length(T_in),1);         % [rad] steering angle
u1 = [T_in Throttle_in Delta_in];

%% 2) Only Throttle (NO Steering)
Throttle_in =[linspace(0,4,0.2*length(T_in)),linspace(4,4,0.4*length(T_in)),...    % [m/s^2] Throttle
    linspace(4,-7.85,0.2*length(T_in)),linspace(-7.85,-7.85,0.2*length(T_in))]'; 
Delta_in = zeros(length(T_in),1);       % [rad] steering angle
u2 = [T_in Throttle_in Delta_in];

%% 3) Only Steering (NO Throttle)
% 3a  Constant steering 2°
Throttle_in = zeros(length(T_in),1);           % [m/s^2] Throttle
Delta_in = repmat(pi/90,length(T_in),1);       % [rad] steering angle
u3a = [T_in Throttle_in Delta_in];
% 3b  Ramp steering 36°
Throttle_in = zeros(length(T_in),1);            % [m/s^2] Throttle
Delta_in = linspace(0,pi/5,length(T_in))';      % [rad] steering angle
u3b = [T_in Throttle_in Delta_in];
% 3c  Sinusoidal steering: Amplitude 5°, Frequency 0.2 Hz 
Throttle_in = zeros(length(T_in),1);         % [m/s^2] Throttle
Delta_in = (pi/36)*sin(2*pi*0.2*T_in);       % [rad] steering angle
u3c = [T_in Throttle_in Delta_in];
% 3d  Sinusoidal steering: Amplitude 15°, Frequency 0.2 Hz 
Throttle_in = zeros(length(T_in),1);         % [m/s^2] Throttle
Delta_in = (pi/12)*sin(2*pi*0.2*T_in);       % [rad] steering angle
u3d = [T_in Throttle_in Delta_in];

%% 4) Combined Inputs
% 4a Constant steering with varying throttle
Throttle_in =[linspace(0,4,0.2*length(T_in)),linspace(4,4,0.4*length(T_in)),...    % [m/s^2] Throttle
    linspace(4,-7.85,0.2*length(T_in)),linspace(-7.85,-7.85,0.2*length(T_in))]'; 
Delta_in = repmat(pi/90,length(T_in),1);       % [rad] steering angle
u4a = [T_in Throttle_in Delta_in];
% 4b Constant throttle with ramp steering
Throttle_in = repmat(0.2,length(T_in),1);            % [m/s^2] Throttle
Delta_in = linspace(0,pi/5,length(T_in))';           % [rad] steering angle
u4b = [T_in Throttle_in Delta_in];