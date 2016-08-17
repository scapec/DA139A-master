function [] = connect(port, dT, T, setpoint, Kp, Ki, Kd)

divider = 10;

arduino = serial(port, 'BaudRate', 115200,'databits', 8);
fopen(arduino);

e = [];
o = [];
d = [];
sp = [];

N = T / dT;
disp(['Amount of iterations(N): ' num2str(N)]);
disp(['Kp: ' num2str(Kp)]);
disp(['Ki: ' num2str(Ki)]);
disp(['Kd: ' num2str(Kd)]);
disp(['Setpoint: ' num2str(setpoint)]);
disp('Sending data to Arduino...');
x = 1:N;

%Clear uart buffer
flushinput(arduino);
flushoutput(arduino);

%Convert to values arduino can read
Kp = Kp*divider;
Ki = Ki*divider;
Kd = Kd*divider;


pause(0.5);
fwrite(arduino, Kp, 'int8');
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
test =  fscanf(arduino,'%d');
disp(['Kp: ' num2str(test)]);

pause(0.5);
fwrite(arduino, Ki, 'int8');
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
test =  fscanf(arduino,'%d');
disp(['Ki: ' num2str(test)]);

pause(0.5);
fwrite(arduino, Kd, 'int8');
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
test =  fscanf(arduino,'%d');
disp(['Kd: ' num2str(test)]);

pause(0.5);
fwrite(arduino, setpoint, 'int8');
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
test =  fscanf(arduino,'%d');
disp(['setpoint: ' num2str(test)]);

pause(1);
% Send startsignal to Arduino
fwrite(arduino, 1, 'int8');
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
test =  fscanf(arduino,'%d');
disp(['PRESET DONE: ' num2str(test)]);
pause(1);

while(arduino.BytesAvailable <= 0)
        pause(0.01);
end
test =  fscanf(arduino,'%d');
disp(['PID STARTED IF 9: ' num2str(test)]);
pause(1);

disp('Starting sampling...');
%Clear uart buffer
flushinput(arduino);
flushoutput(arduino)
for i = 1:N
    start = cputime; %startar en timer för att kunna mäta tiden för en loop
    
    % Signal Arduino Matlab wants values now
    fwrite(arduino, 1, 'int8');
    
    %disp('Wait for values')
    %Wait here until Arduino sends values
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
    % startPID('com3', 0.5, 120, 30, 165, 125, 31, 5)
    %disp('Reading values')
    
    %Read values from Arduino
    error =  fscanf(arduino,'%d');
    pid_output =  fscanf(arduino,'%d');
    distance =  fscanf(arduino,'%d');
    setPoint = fscanf(arduino, '%d');
    
disp(['Error: ' num2str(error)  9 9 'Utsignal: ' num2str(pid_output)  9 9 'Sensor Distans: '  num2str(distance)  9 9 'Setpoint: '  num2str(setPoint)]);
     
     
    e(i) = error;
    o(i) = pid_output;
    d(i) = distance;
    sp(i) = setPoint;
    
    tq(i) = i*dT;
    if(tq(i)<1)
        tq(i)=1;
    end
    
   
    
    plot(tq, sp,'green',tq,e,'red',tq,o,'black',tq,d,'blue');
    ylim([-3000 4000 ]);
    xlabel('Tid(s)');
    ylabel('Position');
    title('PingPong - model');
    legend('Setpoint','Error','Output Value', 'Distance');
    grid on
    
    elapsed=cputime-start; % räknar åtgången tid i sekunder
    ok=(dT-elapsed); % sparar tidsmarginalen i ok
    pause(ok); % pausar resterande samplingstid
end

fclose(instrfind);
delete(instrfind);
clear instrfind

end