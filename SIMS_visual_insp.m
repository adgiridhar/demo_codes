//code.m
%8-13
%104
%2,last tick in EEG lab
%after bandpass:
t0 = 1:617000:9872000
t0 = t0 -1;
t0_ = 1:617000;
for i = 1:16
A__(i,:) = A_(t0(i)+t0_,1);
end
%//////////
t0 = 1:size(A,2):size(A_,1)
t0 = t0 -1;
t0_ = 1:size(A,2);
for i = 1:16
A__(i,:) = A_(t0(i)+t0_,1);
end
%//////////////////
t0 = 1:750:45000;
cd = 'C:\Users\Giridhar A D\Documents\AI\CNS\Gen\Softwares\eeglab13_4_4b\data\Subject data\plots\1\0_';
for i=1:60
y = bl_(:,t0(i):t0(i)+749);
%i=4;
t = linspace(floor(t0(i)/250),floor(t0(i)/250)+(size(y,2)/250),size(y,2));
sig = y(size(y,1):-1:1,:);

% calculate shift
mi = min(sig,[],2);
ma = max(sig,[],2);
shift = cumsum([0; abs(ma(1:end-1))+abs(mi(2:end))]);
shift = repmat(shift,1,size(y,2));

%plot 'eeg' data
%figure visibility off to avoid plot display
figure('Visible','off')
p = plot(t,sig+shift)


% edit axes
set(gca,'ytick',mean(sig+shift,2),'yticklabel',size(y,1):-1:1)
grid on
ylim([mi(1) max(max(shift+sig))])

%save file after editing axes
saveas(gcf,strcat(cd,num2str(i),'_0'),'jpeg');
%C:\Users\Giridhar A D\Documents\AI\CNS\Gen\Softwares\eeglab13_4_4b\data\Subject data\plots
end
%^for baseline 60 plots
%-----------------------------------
cd = 'C:\Users\Giridhar A D\Documents\AI\CNS\Gen\Softwares\eeglab13_4_4b\data\Subject data\plots\1\';
cd_bp = 'C:\Users\Giridhar A D\Documents\AI\CNS\Gen\Softwares\eeglab13_4_4b\data\Subject data\plots\1\bandpass\';
%t1-baseline
for p = 1:6
for t = 1:15
y = A(:,t1_(t,p):t1_(t,p)+749); 
%i=4;
t_ = linspace(floor(t1_(t,p)/250),floor(t1_(t,p)/250)+(size(y,2)/250),size(y,2));
sig = y(size(y,1):-1:1,:);
% calculate shift
mi = min(sig,[],2);
ma = max(sig,[],2);
shift = cumsum([0; abs(ma(1:end-1))+abs(mi(2:end))]);
shift = repmat(shift,1,size(y,2));
%plot 'eeg' data
%figure visibility off to avoid plot display
figure('Visible','off')
p_ = plot(t_,sig+shift)
% edit axes
set(gca,'ytick',mean(sig+shift,2),'yticklabel',size(y,1):-1:1)
grid on
ylim([mi(1) max(max(shift+sig))])
%save file after editing axes
saveas(gcf,strcat(cd,num2str(p),'_',num2str(t),'_0'),'jpeg');
end
end
%-----------------------------------
%t1-action_perf
for p = 1:6
for t = 1:15
y = A(:,t1_(t,p+7):t1_(t,p+7)+999);
%i=4;
t_ = linspace(floor(t1_(t,p+7)/250),floor(t1_(t,p+7)/250)+(size(y,2)/250),size(y,2));
sig = y(size(y,1):-1:1,:);
% calculate shift
mi = min(sig,[],2);
ma = max(sig,[],2);
shift = cumsum([0; abs(ma(1:end-1))+abs(mi(2:end))]);
shift = repmat(shift,1,size(y,2));
%plot 'eeg' data
%figure visibility off to avoid plot display
figure('Visible','off')
p_ = plot(t_,sig+shift)
% edit axes
set(gca,'ytick',mean(sig+shift,2),'yticklabel',size(y,1):-1:1)
grid on
ylim([mi(1) max(max(shift+sig))])
%save file after editing axes
saveas(gcf,strcat(cd,num2str(p),'_',num2str(t),'_1'),'jpeg');
end
end
%-----------------------------------
%-----------------------------------
%t1-baseline_action_power
cd_pow = 'C:\Users\Giridhar A D\Documents\AI\CNS\Gen\Softwares\eeglab13_4_4b\data\Subject data\plots\20\bandpass\power\';
for p = 1:6
%y = zeros(16,1750);
for t = 1:15
y = power([A__(:,t1_(t,p):t1_(t,p)+749) A__(:,t1_(t,p+7):t1_(t,p+7)+999)],2);
%y = y + power([A_(:,t1_(t,p):t1_(t,p)+749) A_(:,t1_(t,p+7):t1_(t,p+7)+999)],2);
%end
y = y/t;
%i=4;
%t_ = linspace(floor(t1_(t,p)/250),floor(t1_(t,p+7)/250)+4,size(y,2));
t_ = linspace(-3,4,size(y,2));
sig = y(size(y,1):-1:1,:);
% calculate shift
mi = min(sig,[],2);
ma = max(sig,[],2);
shift = cumsum([0; abs(ma(1:end-1))+abs(mi(2:end))]);
shift = repmat(shift,1,size(y,2));
%plot 'eeg' data
%figure visibility off to avoid plot display
figure('Visible','off')
p_ = plot(t_,sig+shift)
% edit axes
set(gca,'ytick',mean(sig+shift,2),'yticklabel',size(y,1):-1:1)
grid on
ylim([mi(1) max(max(shift+sig))])
%save file after editing axes
saveas(gcf,strcat(cd_pow,num2str(p),'_',num2str(t),'_2'),'jpeg');
end
end
%-----------------------------------
%t2-baseline_action_power
%cd_pow = 'C:\Users\Giridhar A D\Documents\AI\CNS\Gen\Softwares\eeglab13_4_4b\data\Subject data\plots\3\bandpass\power\';
for p = 1:2
for t = 1:10
y = power([A__(:,t2_(t,p):t2_(t,p)+749) A__(:,t2_(t,p+5):t2_(t,p+5)+1249)],2);

%i=4;
t_ = linspace(floor(t2_(t,p)/250),floor(t2_(t,p+5)/250)+5,size(y,2));
sig = y(size(y,1):-1:1,:);
% calculate shift
mi = min(sig,[],2);
ma = max(sig,[],2);
shift = cumsum([0; abs(ma(1:end-1))+abs(mi(2:end))]);
shift = repmat(shift,1,size(y,2));
%plot 'eeg' data
%figure visibility off to avoid plot display
figure('Visible','off')
p_ = plot(t_,sig+shift)
% edit axes
set(gca,'ytick',mean(sig+shift,2),'yticklabel',size(y,1):-1:1)
grid on
ylim([mi(1) max(max(shift+sig))])
%save file after editing axes
saveas(gcf,strcat(cd_pow,num2str(p+6),'_',num2str(t),'_2'),'jpeg');
end
end
%t2-baseline_action_power_a&h
%cd_pow = 'C:\Users\Giridhar A D\Documents\AI\CNS\Gen\Softwares\eeglab13_4_4b\data\Subject data\plots\3\bandpass\power\';
for p = 3:4
for t = 1:20
y = power([A__(:,t2_(t,p):t2_(t,p)+749) A__(:,t2_(t,p+5):t2_(t,p+5)+1249)],2);

%i=4;
t_ = linspace(floor(t2_(t,p)/250),floor(t2_(t,p+5)/250)+5,size(y,2));
sig = y(size(y,1):-1:1,:);
% calculate shift
mi = min(sig,[],2);
ma = max(sig,[],2);
shift = cumsum([0; abs(ma(1:end-1))+abs(mi(2:end))]);
shift = repmat(shift,1,size(y,2));
%plot 'eeg' data
%figure visibility off to avoid plot display
figure('Visible','off')
p_ = plot(t_,sig+shift)
% edit axes
set(gca,'ytick',mean(sig+shift,2),'yticklabel',size(y,1):-1:1)
grid on
ylim([mi(1) max(max(shift+sig))])
%save file after editing axes
saveas(gcf,strcat(cd_pow,num2str(p+6),'_',num2str(t),'_2'),'jpeg');
end
end
