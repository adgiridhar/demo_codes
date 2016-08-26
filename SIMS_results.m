//results.m
% bl 1 sec f
%for FCz
Y = zeros(1,250);
	for i=1:250:45000
	Y = Y + abs(fft(bl(10,i:i+249)));
	end
	bl_C3_f = Y/180;
Y = zeros(1,250);
	for i=1:250:45000
	Y = Y + abs(fft(bl(11,i:i+249)));
	end
	bl_C4_f = Y/180;
Y = zeros(1,250);
	for i=1:250:45000
	Y = Y + abs(fft(bl(12,i:i+249)));
	end
	bl_FC3_f = Y/180;
Y = zeros(1,250);
	for i=1:250:45000
	Y = Y + abs(fft(bl(13,i:i+249)));
	end
	bl_FC4_f = Y/180;
Y = zeros(1,250);
	for i=1:250:45000
	Y = Y + abs(fft(bl(14,i:i+249)));
	end
	bl_CP3_f = Y/180;
Y = zeros(1,250);
	for i=1:250:45000
	Y = Y + abs(fft(bl(15,i:i+249)));
	end
	bl_CP4_f = Y/180;
    
results = zeros(160,42);
mot_results_C3 = zeros(90,250);
mot_results_C4 = zeros(90,250);
mot_results_FC3 = zeros(90,250);
mot_results_FC4 = zeros(90,250);
mot_results_CP3 = zeros(90,250);
mot_results_CP4 = zeros(90,250);

for i=1:90
    Y = zeros(1,250);
    for j=1:250:1000
        Y = Y + abs(fft(pr_motor_C3(i,j:j+249)));
    end
    Y=Y/4;
    mot_results_C3(i,:) = (bl_C3_f-Y)./bl_C3_f*100; 
end
for i=1:90
    Y = zeros(1,250);
    for j=1:250:1000
        Y = Y + abs(fft(pr_motor_C4(i,j:j+249)));
    end
    Y=Y/4;
    mot_results_C4(i,:) = (bl_C4_f-Y)./bl_C4_f*100; 
end
for i=1:90
    Y = zeros(1,250);
    for j=1:250:1000
        Y = Y + abs(fft(pr_motor_FC3(i,j:j+249)));
    end
    Y=Y/4;
    mot_results_FC3(i,:) = (bl_FC3_f-Y)./bl_FC3_f*100; 
end
for i=1:90
    Y = zeros(1,250);
    for j=1:250:1000
        Y = Y + abs(fft(pr_motor_FC4(i,j:j+249)));
    end
    Y=Y/4;
    mot_results_FC4(i,:) = (bl_FC4_f-Y)./bl_FC4_f*100; 
end
for i=1:90
    Y = zeros(1,250);
    for j=1:250:1000
        Y = Y + abs(fft(pr_motor_CP3(i,j:j+249)));
    end
    Y=Y/4;
    mot_results_CP3(i,:) = (bl_CP3_f-Y)./bl_CP3_f*100; 
end
for i=1:90
    Y = zeros(1,250);
    for j=1:250:1000
        Y = Y + abs(fft(pr_motor_CP4(i,j:j+249)));
    end
    Y=Y/4;
    mot_results_CP4(i,:) = (bl_CP4_f-Y)./bl_CP4_f*100; 
end

j=8;
for i=1:7:42
    results(1:90,i) = mot_results_C3(:,j);
    j = j+1;
end
j=8;
for i=1:7:42
    results(1:90,i+1) = mot_results_C4(:,j);
    j = j+1;
end
j=8;
for i=1:7:42
    results(1:90,i+2) = mot_results_FC3(:,j);
    j = j+1;
end
j=8;
for i=1:7:42
    results(1:90,i+3) = mot_results_FC4(:,j);
    j = j+1;
end
j=8;
for i=1:7:42
    results(1:90,i+4) = mot_results_CP3(:,j);
    j = j+1;
end
j=8;
for i=1:7:42
    results(1:90,i+5) = mot_results_CP4(:,j);
    j = j+1;
end

results(91,:) = sum(results(RP,:))/15;
results(92,:) = sum(results(LP,:))/15;
results(93,:) = sum(results(RO,:))/15;
results(94,:) = sum(results(LO,:))/15;
results(95,:) = sum(results(RI,:))/15;
results(96,:) = sum(results(LI,:))/15;

emp_results_C3 = zeros(60,250);
emp_results_C4 = zeros(60,250);
emp_results_FC3 = zeros(60,250);
emp_results_FC4 = zeros(60,250);
emp_results_CP3 = zeros(60,250);
emp_results_CP4 = zeros(60,250);
%for FCz ; change accorrindlyt for Cz
for i=1:10
    Y1 = zeros(1,250);
    Y2 = zeros(1,250);
    Y3 = zeros(1,250);
    Y4 = zeros(1,250);
    Y5 = zeros(1,250);
    Y6 = zeros(1,250);
    for j=1:250:1250
        Y1 = Y1 + abs(fft(pr_emp_n(C3(i)+9,j:j+249)));
        Y2 = Y2 + abs(fft(pr_emp_n(C3(i)+10,j:j+249)));
        Y3 = Y3 + abs(fft(pr_emp_n(C3(i)+11,j:j+249)));
        Y4 = Y4 + abs(fft(pr_emp_n(C3(i)+12,j:j+249)));
        Y5 = Y5 + abs(fft(pr_emp_n(C3(i)+13,j:j+249)));
        Y6 = Y6 + abs(fft(pr_emp_n(C3(i)+14,j:j+249)));
    end
    Y1=Y1/5; Y2=Y2/5; Y3=Y3/5; Y4=Y4/5; Y5=Y5/5; Y6=Y6/5;
    emp_results_C3(i,:) = (bl_C3_f-Y1)./bl_C3_f*100;
    emp_results_C4(i,:) = (bl_C4_f-Y2)./bl_C4_f*100;
    emp_results_FC3(i,:) = (bl_FC3_f-Y3)./bl_FC3_f*100;
    emp_results_FC4(i,:) = (bl_FC4_f-Y4)./bl_FC4_f*100;
    emp_results_CP3(i,:) = (bl_CP3_f-Y5)./bl_CP3_f*100;
    emp_results_CP4(i,:) = (bl_CP4_f-Y6)./bl_CP4_f*100;
end
for i=11:20
    Y1 = zeros(1,250);
    Y2 = zeros(1,250);
    Y3 = zeros(1,250);
    Y4 = zeros(1,250);
    Y5 = zeros(1,250);
    Y6 = zeros(1,250);
    for j=1:250:1250
        Y1 = Y1 + abs(fft(pr_emp_n_n(C3(i-10)+9,j:j+249)));
        Y2 = Y2 + abs(fft(pr_emp_n_n(C3(i-10)+10,j:j+249)));
        Y3 = Y3 + abs(fft(pr_emp_n_n(C3(i-10)+11,j:j+249)));
        Y4 = Y4 + abs(fft(pr_emp_n_n(C3(i-10)+12,j:j+249)));
        Y5 = Y5 + abs(fft(pr_emp_n_n(C3(i-10)+13,j:j+249)));
        Y6 = Y6 + abs(fft(pr_emp_n_n(C3(i-10)+14,j:j+249)));
    end
    Y1=Y1/5; Y2=Y2/5; Y3=Y3/5; Y4=Y4/5; Y5=Y5/5; Y6=Y6/5;
    emp_results_C3(i,:) = (bl_C3_f-Y1)./bl_C3_f*100;
    emp_results_C4(i,:) = (bl_C4_f-Y2)./bl_C4_f*100;
    emp_results_FC3(i,:) = (bl_FC3_f-Y3)./bl_FC3_f*100;
    emp_results_FC4(i,:) = (bl_FC4_f-Y4)./bl_FC4_f*100;
    emp_results_CP3(i,:) = (bl_CP3_f-Y5)./bl_CP3_f*100;
    emp_results_CP4(i,:) = (bl_CP4_f-Y6)./bl_CP4_f*100;
end
for i=21:40
    Y1 = zeros(1,250);
    Y2 = zeros(1,250);
    Y3 = zeros(1,250);
    Y4 = zeros(1,250);
    Y5 = zeros(1,250);
    Y6 = zeros(1,250);
    for j=1:250:1250
        Y1 = Y1 + abs(fft(pr_emp_h(C3(i-20)+9,j:j+249)));
        Y2 = Y2 + abs(fft(pr_emp_h(C3(i-20)+10,j:j+249)));
        Y3 = Y3 + abs(fft(pr_emp_h(C3(i-20)+11,j:j+249)));
        Y4 = Y4 + abs(fft(pr_emp_h(C3(i-20)+12,j:j+249)));
        Y5 = Y5 + abs(fft(pr_emp_h(C3(i-20)+13,j:j+249)));
        Y6 = Y6 + abs(fft(pr_emp_h(C3(i-20)+14,j:j+249)));
    end
    Y1=Y1/5; Y2=Y2/5; Y3=Y3/5; Y4=Y4/5; Y5=Y5/5; Y6=Y6/5;
    emp_results_C3(i,:) = (bl_C3_f-Y1)./bl_C3_f*100;
    emp_results_C4(i,:) = (bl_C4_f-Y2)./bl_C4_f*100;
    emp_results_FC3(i,:) = (bl_FC3_f-Y3)./bl_FC3_f*100;
    emp_results_FC4(i,:) = (bl_FC4_f-Y4)./bl_FC4_f*100;
    emp_results_CP3(i,:) = (bl_CP3_f-Y5)./bl_CP3_f*100;
    emp_results_CP4(i,:) = (bl_CP4_f-Y6)./bl_CP4_f*100;
end
for i=41:60
    Y1 = zeros(1,250);
    Y2 = zeros(1,250);
    Y3 = zeros(1,250);
    Y4 = zeros(1,250);
    Y5 = zeros(1,250);
    Y6 = zeros(1,250);
    for j=1:250:1250
        Y1 = Y1 + abs(fft(pr_emp_a(C3(i-40)+9,j:j+249)));
        Y2 = Y2 + abs(fft(pr_emp_a(C3(i-40)+10,j:j+249)));
        Y3 = Y3 + abs(fft(pr_emp_a(C3(i-40)+11,j:j+249)));
        Y4 = Y4 + abs(fft(pr_emp_a(C3(i-40)+12,j:j+249)));
        Y5 = Y5 + abs(fft(pr_emp_a(C3(i-40)+13,j:j+249)));
        Y6 = Y6 + abs(fft(pr_emp_a(C3(i-40)+14,j:j+249)));
    end
    Y1=Y1/5; Y2=Y2/5; Y3=Y3/5; Y4=Y4/5; Y5=Y5/5; Y6=Y6/5;
    emp_results_C3(i,:) = (bl_C3_f-Y1)./bl_C3_f*100;
    emp_results_C4(i,:) = (bl_C4_f-Y2)./bl_C4_f*100;
    emp_results_FC3(i,:) = (bl_FC3_f-Y3)./bl_FC3_f*100;
    emp_results_FC4(i,:) = (bl_FC4_f-Y4)./bl_FC4_f*100;
    emp_results_CP3(i,:) = (bl_CP3_f-Y5)./bl_CP3_f*100;
    emp_results_CP4(i,:) = (bl_CP4_f-Y6)./bl_CP4_f*100;
end

n = 98:98+9;
n_n = 108:108+9;
h = 118:118+19;
a = 138:138+19;

% for FCZ
C3_ = 1:7:41;
results(n,C3_) = emp_results_C3(1:10,8:13);
results(n,C3_+1) = emp_results_C4(1:10,8:13);
results(n,C3_+2) = emp_results_FC3(1:10,8:13);
results(n,C3_+3) = emp_results_FC4(1:10,8:13);
results(n,C3_+4) = emp_results_CP3(1:10,8:13);
results(n,C3_+5) = emp_results_CP4(1:10,8:13);

results(n_n,C3_) = emp_results_C3(11:20,8:13);
results(n_n,C3_+1) = emp_results_C4(11:20,8:13);
results(n_n,C3_+2) = emp_results_FC3(11:20,8:13);
results(n_n,C3_+3) = emp_results_FC4(11:20,8:13);
results(n_n,C3_+4) = emp_results_CP3(11:20,8:13);
results(n_n,C3_+5) = emp_results_CP4(11:20,8:13);

results(h,C3_) = emp_results_C3(21:40,8:13);
results(h,C3_+1) = emp_results_C4(21:40,8:13);
results(h,C3_+2) = emp_results_FC3(21:40,8:13);
results(h,C3_+3) = emp_results_FC4(21:40,8:13);
results(h,C3_+4) = emp_results_CP3(21:40,8:13);
results(h,C3_+5) = emp_results_CP4(21:40,8:13);

results(a,C3_) = emp_results_C3(41:60,8:13);
results(a,C3_+1) = emp_results_C4(41:60,8:13);
results(a,C3_+2) = emp_results_FC3(41:60,8:13);
results(a,C3_+3) = emp_results_FC4(41:60,8:13);
results(a,C3_+4) = emp_results_CP3(41:60,8:13);
results(a,C3_+5) = emp_results_CP4(41:60,8:13);

results(158,:) = sum(results(n,:))/10;
results(159,:) = sum(results(n_n,:))/10;
results(160,:) = sum(results(h,:))/20;
results(161,:) = sum(results(a,:))/20;
%
csvwrite('results.csv',results);
%///////////////
subplot(2,1,1)
temp = power([A__(:,t1_(t,p):t1_(t,p)+749) A__(:,t1_(t,p+7):t1_(t,p+7)+999)],2);
plot(temp(15,:))
subplot(2,1,2)
temp = [A__(:,t1_(t,p):t1_(t,p)+749) A__(:,t1_(t,p+7):t1_(t,p+7)+999)];
plot(temp(15,:))
%///////////////////
for i=1:125:1750
sum(temp(15,i:i+124))/125
end
%...............
for i=1:125:1750
((sum(temp(15,1:750))/750)-sum(temp(15,i:i+124))/125)*100/(sum(temp(15,1:750))/750)
end
%.../././././.
for i=1:125:1750
log((sum(temp(15,i:i+124))/125)/(sum(temp(15,1:750))/750))
end
