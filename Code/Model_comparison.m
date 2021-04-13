%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script built to make a comparison between kinematic and       %
% linearized vehicle model with dynamic non linear vehicle      %
% model.                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


clear all
close all
clc

% include useful folders
addpath('./Scripts');
addpath('./Files');
addpath('./SimulinkModels');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% PARAMETERS FOR DYNAMIC MODEL  %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

param = loadParameters(0);       % Load vehicle parameters
V= 20/3.6;                      % [m/s] Vehicle speed

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% SIMULATION SETUP %%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ts = 0.001;                     % [s] Sampling time
T_fin = 100;                     % [s] Duration of simulation
T_in = linspace(0,T_fin,1000)';      % Input time vector



Throttle_in = zeros(length(T_in),1);            % [m/s^2] Throttle
Delta_in = sin(T_in./(2.*pi).*2).*pi/120;       % [rad] steering angle

% Create a structure suitable for Simulink Test tool
u_test = [T_in Throttle_in Delta_in];           % Input structure
param_test = [[0;T_fin] [param';param']];       % Parameters structure

x0_dyn = [0; 0; 0; V; 0; 0; 0; 0; 0];          % Initial condition for dynamic model
x0_kin = [0; 0; 0; V];                         % Initial condition for kinematic model