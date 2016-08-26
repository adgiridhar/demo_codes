//cpp
#include<iostream.h>
#include<conio.h>
float y=0, y_in=0;
float init_W=0;
float init_B=0;
float alpha=1;
float threshold=1;
int flag=0;
int zero=0;
int zero_=-1;
float s[10][7]=	{
		{1,1,1,1,1,1,zero},//0
		{zero,1,1,zero,zero,zero,zero},//1
		{1,1,zero,1,1,zero,1},//2
		{1,1,1,1,zero,zero,1},//3
		{zero,1,1,zero,zero,1,1},//4
		{1,zero,1,1,zero,1,1},//5
		{1,zero,1,1,1,1,1},//6
		{1,1,1,zero,zero,zero,zero},//7
		{1,1,1,1,1,1,1},//8
		{1,1,1,zero,zero,1,1}//9
		};
float t[10]={zero_,zero_,zero_,zero_,zero_,zero_,zero_,zero_,1,1};//8
//float t[10]={zero_,zero_,zero_,zero_,1,1,1,1,zero_,zero_};//4
//float t[10]={zero_,zero_,1,1,zero_,zero_,1,1,zero_,zero_};//2
//float t[10]={zero_,1,zero_,1,zero_,1,zero_,1,zero_,1};//1
int temp[7]={0,0,0,0,0,0,0};
float w[7]={init_W,init_W,init_W,init_W,init_W,init_W,init_W};
float b=init_B;
float sum(int[]);
float out(float);
void main()
{
clrscr();
float sigma=0,i=0,j=0,count=0;
while(!flag&&count<1000)
	{
	flag=1;
	count++;
	for(i=0;i<10;i++)
		{
		y_in=0;
		y=0;
		sigma=0;
		for(j=0;j<7;j++)
			sigma+=s[i][j]*w[j];
		y_in = b+sigma;
		y = out(y_in);
		cout<<endl<<count<<" "<<i<<" "<<j<<" "<<y_in<<" "<<y<<":"<<t[i];
		if(y!=t[i])
			{
			flag=0;
			for(j=0;j<7;j++)
				w[j]+=(alpha*(t[i])*s[i][j]);
			b+=(alpha*(t[i]));
			}
		}
	}
cout<<endl<<count<<endl<<b<<endl;
for(i=0;i<7;i++)cout<<w[i]<<" ";
getch();
}
float sum(int m[7])
{
int temp=0;
for(int i=0; i<7; i++) temp+=m[i];
return temp;
}
float out(float yin)
{
if(yin>=threshold) return 1;
else if((yin>(-1*threshold))&&(yin<threshold)) return 0;
else return -1;
}
//arduino
int one = 7;
int two = 8;
int three = 9;
int four = 10;
int five = 11;
int six = 12;
int seven = 13;
int pin1 = 21;
int pin2 = 20;
int pin3 = 19;
int pin4 = 18;
int pin5 = 17;
int pin6 = 16;
int pin7 = 15;
int b1,b2,b3,b4,b5,b6,b7,bc;
int pb1,pb2,pb3,pb4,pb5,pb6,pb7,pbc;
int f1=0,f2=0,f3=0,f4=0,f5=0,f6=0,f7=0;
int clear_ = 14;
int dec=0;
void setup()
{
  Serial.begin(9600);
  pinMode(one,OUTPUT);
  pinMode(two,OUTPUT);
  pinMode(three,OUTPUT);
  pinMode(four,OUTPUT);
  pinMode(five,OUTPUT);
  pinMode(six,OUTPUT);
  pinMode(seven,OUTPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  pinMode(pin4,INPUT);
  pinMode(pin5,INPUT);
  pinMode(pin6,INPUT);
  pinMode(pin7,INPUT);
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,HIGH);
  digitalWrite(pin6,HIGH);
  digitalWrite(pin7,HIGH);
  pinMode(clear_,INPUT);
  digitalWrite(clear_,HIGH);
  clear();
}
void loop()
{
  press_buttons();
  
  display_number();
}
void active(int a)
{
  digitalWrite(a,LOW);
}
void deactive(int a)
{
  digitalWrite(a,HIGH);
}
void test1()
{
  active(one);
  delay(100);
  deactive(one);
  active(two);
  delay(100);
  deactive(two);
  active(three);
  delay(100);
  deactive(three);
  active(four);
  delay(100);
  deactive(four);
  active(five);
  delay(100);
  deactive(five);
  active(six);
  delay(100);
  deactive(six);
}
void clear()
{
  digitalWrite(one,HIGH);
  digitalWrite(two,HIGH);
  digitalWrite(three,HIGH);
  digitalWrite(four,HIGH);
  digitalWrite(five,HIGH);
  digitalWrite(six,HIGH);
  digitalWrite(seven,HIGH);
}
void _1()
{
  active(two);
  active(three);
}
void _2()
{
  active(one);
  active(two);
  active(four);
  active(five);
  active(seven);
}
void _3()
{
  active(one);
  active(two);
  active(three);
  active(four);
  active(seven);
}
void _4()
{
  active(two);
  active(three);
  active(six);
  active(seven);
}
void _5()
{
  active(one);
  active(three);
  active(four);
  active(six);
  active(seven);
}
void _6()
{
  active(one);
  active(three);
  active(four);
  active(five);
  active(six);
  active(seven);
}
void _7()
{
  active(one);
  active(two);
  active(three);
}
void _8()
{
  active(one);
  active(two);
  active(three);
  active(four);
  active(five);
  active(six);
  active(seven);
}
void _9()
{
  active(one);
  active(two);
  active(three);
  active(six);
  active(seven);
}
void _0()
{
  active(one);
  active(two);
  active(three);
  active(four);
  active(five);
  active(six);
}
void check_buttons()
{
  if(!digitalRead(pin1)) b1=1;
  else b1=0;

  if(!digitalRead(pin2)) b2=1;
  else b2=0;

  if(!digitalRead(pin3)) b3=1;
  else b3=0;

  if(!digitalRead(pin4)) b4=1;
  else b4=0;

  if(!digitalRead(pin5)) b5=1;
  else b5=0;

  if(!digitalRead(pin6)) b6=1;
  else b6=0;

  if(!digitalRead(pin7)) b7=1;
  else b7=0;

  //delay(5);
}
void display_buttons()
{
  if(b1) active(one);
  else deactive(one);
  
  if(b2) active(two);
  else deactive(two);
  
  if(b3) active(three);
  else deactive(three);
  
  if(b4) active(four);
  else deactive(four);
  
  if(b5) active(five);
  else deactive(five);
  
  if(b6) active(six);
  else deactive(six);
  
  if(b7) active(seven);
  else deactive(seven);
}
void test_buttons()
{
  Serial.print(digitalRead(pin1));
  Serial.print(" ");
  Serial.print(digitalRead(pin2));
  Serial.print(" ");
  Serial.print(digitalRead(pin3));
  Serial.print(" ");
  Serial.print(digitalRead(pin4));
  Serial.print(" ");
  Serial.print(digitalRead(pin5));
  Serial.print(" ");
  Serial.print(digitalRead(pin6));
  Serial.print(" ");
  Serial.print(digitalRead(pin7));
  Serial.println(" ");
}
void press_buttons()
{
  b1=!digitalRead(pin1);
  b2=!digitalRead(pin2);
  b3=!digitalRead(pin3);
  b4=!digitalRead(pin4);
  b5=!digitalRead(pin5);
  b6=!digitalRead(pin6);
  b7=!digitalRead(pin7);
  bc=!digitalRead(clear_);
  
  if(!b1 & pb1)
    {
      if(!f1) f1=1;
      else if(f1)  f1=0;
      //Serial.print(1);
      //Serial.print(" ");
      //Serial.println(f1);
      delay(5);
    }
  if(!b2 & pb2)
    {
      if(!f2) f2=1;
      else if(f2)  f2=0;
      //Serial.print(2);
      //Serial.print(" ");
      //Serial.println(f2);
      delay(5);
    }
  if(!b3 & pb3)
    {
      if(!f3) f3=1;
      else if(f3)  f3=0;
      //Serial.print(3);
      //Serial.print(" ");
      //Serial.println(f3);
      delay(5);
    }
  if(!b4 & pb4)
    {
      if(!f4) f4=1;
      else if(f4)  f4=0;
      //Serial.print(4);
      //Serial.print(" ");
      //Serial.println(f4);
      delay(5);
    }
  if(!b5 & pb5)
    {
      if(!f5) f5=1;
      else if(f5)  f5=0;
      //Serial.print(5);
      //Serial.print(" ");
      //Serial.println(f5);
      delay(5);
    }
  if(!b6 & pb6)
    {
      if(!f6) f6=1;
      else if(f6)  f6=0;
      //Serial.print(6);
      //Serial.print(" ");
      //Serial.println(f6);
      delay(5);
    }
  if(!b7 & pb7)
    {
      if(!f7) f7=1;
      else if(f7)  f7=0;
      //Serial.print(7);
      //Serial.print(" ");
      //Serial.println(f7);
      delay(5);
    }
   
   if(!bc & pbc) 
     {
       calc_number();
       Serial.println(dec);
       f1=0;
       f2=0;
       f3=0;
       f4=0;
       f5=0;
       f6=0;
       f7=0;
     }
    
   pb1=b1;
   pb2=b2;
   pb3=b3;
   pb4=b4;
   pb5=b5;
   pb6=b6;
   pb7=b7;
   pbc=bc;
}
void display_number()
{
  if(f1) active(one);
  else deactive(one);
  
  if(f2) active(two);
  else deactive(two);
  
  if(f3) active(three);
  else deactive(three);
  
  if(f4) active(four);
  else deactive(four);
  
  if(f5) active(five);
  else deactive(five);
  
  if(f6) active(six);
  else deactive(six);
  
  if(f7) active(seven);
  else deactive(seven);
}
void calc_number()
{
int x[7] = {f1,f2,f3,f4,f5,f6,f7};
int w[7][4]={	{ 4, 2, 5, 5},
		{ 3,-7,-6,-1},
		{ 2, 3, 1, 2},
		{-2,-5, 2, 0},
		{ 2,-6, 5,-7},
		{ 3, 3,-13,-3},
		{ 7, 3, 1, 0}
	    };
int b[4] = {-18,3,3,1};
int thresh[4] = {1,1,1,1};
int out[4] = {0,0,0,0};
int sigma=0;
dec=0;
  for(int i=0;i<4;i++)
	{
	sigma=0;
	for(int j=0;j<7;j++)
		{
		sigma+=x[j]*w[j][i];
		}
	sigma+=b[i];
	if(sigma>=thresh[i]) out[i]=1;
	else out[i]=0;
	if(i==1 && out[0]==1) out[i]=0;
	}
dec=(8*out[0])+(4*out[1])+(2*out[2])+(1*out[3]);
}
//display
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(24,26,30,32,34,36);
int one = 7;
int two = 8;
int three = 9;
int four = 10;
int five = 11;
int six = 12;
int seven = 13;
int pin1 = 21;
int pin2 = 20;
int pin3 = 19;
int pin4 = 18;
int pin5 = 17;
int pin6 = 16;
int pin7 = 15;
int b1,b2,b3,b4,b5,b6,b7,bc;
int pb1,pb2,pb3,pb4,pb5,pb6,pb7,pbc;
int f1=0,f2=0,f3=0,f4=0,f5=0,f6=0,f7=0;
int clear_ = 14;
int dec=0;
char printVal[30];
int serialData,pserialData;
void setup()
{
  Serial.begin(9600);
  pinMode(one,OUTPUT);
  pinMode(two,OUTPUT);
  pinMode(three,OUTPUT);
  pinMode(four,OUTPUT);
  pinMode(five,OUTPUT);
  pinMode(six,OUTPUT);
  pinMode(seven,OUTPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  pinMode(pin4,INPUT);
  pinMode(pin5,INPUT);
  pinMode(pin6,INPUT);
  pinMode(pin7,INPUT);
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,HIGH);
  digitalWrite(pin6,HIGH);
  digitalWrite(pin7,HIGH);
  pinMode(clear_,INPUT);
  digitalWrite(clear_,HIGH);
  clear();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print(".....PIANNO.....");
  lcd.setCursor(0,1);
  lcd.print("Reading inputs");
}
void loop()
{
  //press_buttons();
  press_serial_buttons();
  display_number();
}
void active(int a)
{
  digitalWrite(a,LOW);
}
void deactive(int a)
{
  digitalWrite(a,HIGH);
}
void test1()
{
  active(one);
  delay(100);
  deactive(one);
  active(two);
  delay(100);
  deactive(two);
  active(three);
  delay(100);
  deactive(three);
  active(four);
  delay(100);
  deactive(four);
  active(five);
  delay(100);
  deactive(five);
  active(six);
  delay(100);
  deactive(six);
}
void clear()
{
  digitalWrite(one,HIGH);
  digitalWrite(two,HIGH);
  digitalWrite(three,HIGH);
  digitalWrite(four,HIGH);
  digitalWrite(five,HIGH);
  digitalWrite(six,HIGH);
  digitalWrite(seven,HIGH);
}
void _1()
{
  active(two);
  active(three);
}
void _2()
{
  active(one);
  active(two);
  active(four);
  active(five);
  active(seven);
}
void _3()
{
  active(one);
  active(two);
  active(three);
  active(four);
  active(seven);
}
void _4()
{
  active(two);
  active(three);
  active(six);
  active(seven);
}
void _5()
{
  active(one);
  active(three);
  active(four);
  active(six);
  active(seven);
}
void _6()
{
  active(one);
  active(three);
  active(four);
  active(five);
  active(six);
  active(seven);
}
void _7()
{
  active(one);
  active(two);
  active(three);
}
void _8()
{
  active(one);
  active(two);
  active(three);
  active(four);
  active(five);
  active(six);
  active(seven);
}
void _9()
{
  active(one);
  active(two);
  active(three);
  active(six);
  active(seven);
}
void _0()
{
  active(one);
  active(two);
  active(three);
  active(four);
  active(five);
  active(six);
}
void check_buttons()
{
  if(!digitalRead(pin1)) b1=1;
  else b1=0;

  if(!digitalRead(pin2)) b2=1;
  else b2=0;

  if(!digitalRead(pin3)) b3=1;
  else b3=0;

  if(!digitalRead(pin4)) b4=1;
  else b4=0;

  if(!digitalRead(pin5)) b5=1;
  else b5=0;

  if(!digitalRead(pin6)) b6=1;
  else b6=0;

  if(!digitalRead(pin7)) b7=1;
  else b7=0;

  //delay(5);
}
void display_buttons()
{
  if(b1) active(one);
  else deactive(one);
  
  if(b2) active(two);
  else deactive(two);
  
  if(b3) active(three);
  else deactive(three);
  
  if(b4) active(four);
  else deactive(four);
  
  if(b5) active(five);
  else deactive(five);
  
  if(b6) active(six);
  else deactive(six);
  
  if(b7) active(seven);
  else deactive(seven);
}
void test_buttons()
{
  Serial.print(digitalRead(pin1));
  Serial.print(" ");
  Serial.print(digitalRead(pin2));
  Serial.print(" ");
  Serial.print(digitalRead(pin3));
  Serial.print(" ");
  Serial.print(digitalRead(pin4));
  Serial.print(" ");
  Serial.print(digitalRead(pin5));
  Serial.print(" ");
  Serial.print(digitalRead(pin6));
  Serial.print(" ");
  Serial.print(digitalRead(pin7));
  Serial.println(" ");
}
void press_buttons()
{
  b1=!digitalRead(pin1);
  b2=!digitalRead(pin2);
  b3=!digitalRead(pin3);
  b4=!digitalRead(pin4);
  b5=!digitalRead(pin5);
  b6=!digitalRead(pin6);
  b7=!digitalRead(pin7);
  bc=!digitalRead(clear_);
  
  if(!b1 & pb1)
    {
      if(!f1) f1=1;
      else if(f1)  f1=0;
      //Serial.print(1);
      //Serial.print(" ");
      //Serial.println(f1);
      //delay(5);
    }
  if(!b2 & pb2)
    {
      if(!f2) f2=1;
      else if(f2)  f2=0;
      //Serial.print(2);
      //Serial.print(" ");
      //Serial.println(f2);
      //delay(5);
    }
  if(!b3 & pb3)
    {
      if(!f3) f3=1;
      else if(f3)  f3=0;
      //Serial.print(3);
      //Serial.print(" ");
      //Serial.println(f3);
      //delay(5);
    }
  if(!b4 & pb4)
    {
      if(!f4) f4=1;
      else if(f4)  f4=0;
      //Serial.print(4);
      //Serial.print(" ");
      //Serial.println(f4);
      //delay(5);
    }
  if(!b5 & pb5)
    {
      if(!f5) f5=1;
      else if(f5)  f5=0;
      //Serial.print(5);
      //Serial.print(" ");
      //Serial.println(f5);
      //delay(5);
    }
  if(!b6 & pb6)
    {
      if(!f6) f6=1;
      else if(f6)  f6=0;
      //Serial.print(6);
      //Serial.print(" ");
      //Serial.println(f6);
      //delay(5);
    }
  if(!b7 & pb7)
    {
      if(!f7) f7=1;
      else if(f7)  f7=0;
      //Serial.print(7);
      //Serial.print(" ");
      //Serial.println(f7);
      //delay(5);
    }
   
   if(!bc & pbc) 
     {
       calc_number();
       print_lcd(dec);
       Serial.println(dec);
       f1=0;
       f2=0;
       f3=0;
       f4=0;
       f5=0;
       f6=0;
       f7=0;
     }
    
   pb1=b1;
   pb2=b2;
   pb3=b3;
   pb4=b4;
   pb5=b5;
   pb6=b6;
   pb7=b7;
   pbc=bc;
}
void press_serial_buttons()
{
  serialData=-1;
  b1=0;
  b2=0;
  b3=0;
  b4=0;
  b5=0;
  b6=0;
  b7=0;
  bc=0;
  if(Serial.available())
  {
  lcd.setCursor(0,1);
  lcd.print("Reading inputs");
  serialData = Serial.parseInt();
  if(serialData==1) {b1=1;}
  else if(serialData==2) {b2=1;}
  else if(serialData==3) {b3=1;}
  else if(serialData==4) {b4=1;}
  else if(serialData==5) {b5=1;}
  else if(serialData==6) {b6=1;}
  else if(serialData==7) {b7=1;}
  else if(serialData==8) {bc=1;}
  else if(serialData==9) 
      {
        f1=0;
        f2=0;
        f3=0;
        f4=0;
        f5=0;
        f6=0;
        f7=0;
      }
  }
  else
  {
  b1=!digitalRead(pin1);
  b2=!digitalRead(pin2);
  b3=!digitalRead(pin3);
  b4=!digitalRead(pin4);
  b5=!digitalRead(pin5);
  b6=!digitalRead(pin6);
  b7=!digitalRead(pin7);
  bc=!digitalRead(clear_);
  }
  if(!b1 & pb1)
    {
      if(!f1) f1=1;
      else if(f1)  f1=0;
      if(pserialData==-1)
        Serial.println("1");
    }
  if(!b2 & pb2)
    {
      if(!f2) f2=1;
      else if(f2)  f2=0;
      if(pserialData==-1)
        Serial.println("2");
    }
  if(!b3 & pb3)
    {
      if(!f3) f3=1;
      else if(f3)  f3=0;
      if(pserialData==-1)
        Serial.println("3");
    }
  if(!b4 & pb4)
    {
      if(!f4) f4=1;
      else if(f4)  f4=0;
      if(pserialData==-1)
        Serial.println("4");
    }
  if(!b5 & pb5)
    {
      if(!f5) f5=1;
      else if(f5)  f5=0;
      if(pserialData==-1)
        Serial.println("5");
    }
  if(!b6 & pb6)
    {
      if(!f6) f6=1;
      else if(f6)  f6=0;
      if(pserialData==-1)
        Serial.println("6");
    }
  if(!b7 & pb7)
    {
      if(!f7) f7=1;
      else if(f7)  f7=0;
      if(pserialData==-1)
        Serial.println("7");
    }
   
   if(!bc & pbc) 
     {
       calc_number();
       if(dec!=-1)
       {
         
       print_lcd(dec);
       dec+=10;
       Serial.println(dec);
       }
       else
       {
         lcd.clear();
         Serial.println(dec);
  lcd.setCursor(0,0);
  lcd.print("No Match Found"); 
  lcd.setCursor(0,1);
  lcd.print("PlzTrainPtrn");
       }
       f1=0;
       f2=0;
       f3=0;
       f4=0;
       f5=0;
       f6=0;
       f7=0;
     }
    
   pb1=b1;
   pb2=b2;
   pb3=b3;
   pb4=b4;
   pb5=b5;
   pb6=b6;
   pb7=b7;
   pbc=bc;
   pserialData = serialData;
}
void display_number()
{
  if(f1) active(one);
  else deactive(one);
  
  if(f2) active(two);
  else deactive(two);
  
  if(f3) active(three);
  else deactive(three);
  
  if(f4) active(four);
  else deactive(four);
  
  if(f5) active(five);
  else deactive(five);
  
  if(f6) active(six);
  else deactive(six);
  
  if(f7) active(seven);
  else deactive(seven);
}
void calc_number()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("RecognisingPatrn"); 
for(int prec=0;prec<37;prec++)
{
lcd.setCursor(12,1);
if(prec<10) lcd.print("00");
else lcd.print("0");
lcd.print(prec);
lcd.print("%");
delay(60);
}
int x[7] = {f1,f2,f3,f4,f5,f6,f7};
int w[7][4]={	{ 4, 2, 5, 5},
		{ 3,-7,-6,-1},
		{ 2, 3, 1, 2},
		{-2,-5, 2, 0},
		{ 2,-6, 5,-7},
		{ 3, 3,-13,-3},
		{ 7, 3, 1, 0}
	    };
int b[4] = {-18,3,3,1};
int thresh[4] = {1,1,1,1};
int out[4] = {0,0,0,0};
int sigma=0;
dec=0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Matching Trained"); 
lcd.setCursor(0,1);
lcd.print("Inputs");
for(int prec=37;prec<82;prec++)
{
lcd.setCursor(12,1);
if(prec<10) lcd.print("00");
else lcd.print("0");
lcd.print(prec);
lcd.print("%");
delay(30);
}
  for(int i=0;i<4;i++)
	{
	sigma=0;
	for(int j=0;j<7;j++)
		{
		sigma+=x[j]*w[j][i];
		}
	sigma+=b[i];
	if(sigma>=thresh[i]) out[i]=1;
	else out[i]=0;
	if(i==1 && out[0]==1) out[i]=0;
	}
dec=(8*out[0])+(4*out[1])+(2*out[2])+(1*out[3]);
int pntr=0, pcount=0;
lcd.clear();
int flag=0;
if(f1 && f2 && f3 && f4 && f5 && f6 && !f7) {flag=1;}//0
else if(!f1 && f2 && f3 && !f4 && !f5 && !f6 && !f7){flag=1;}//1
else if(f1 && f2 && !f3 && f4 && f5 && !f6 && f7){flag=1;}//2
else if(f1 && f2 && f3 && f4 && !f5 && !f6 && f7){flag=1;}//3
else if(!f1 && f2 && f3 && !f4 && !f5 && f6 && f7){flag=1;}//4
else if(f1 && !f2 && f3 && f4 && !f5 && f6 && f7){flag=1;}//5
else if(f1 && !f2 && f3 && f4 && f5 && f6 && f7){flag=1;}//6
else if(f1 && f2 && f3 && !f4 && !f5 && !f6 && !f7){flag=1;}//7
else if(f1 && f2 && f3 && f4 && f5 && f6 && f7){flag=1;}//8
else if(f1 && f2 && f3 && !f4 && !f5 && f6 && f7){flag=1;}//9
else if(f1 && f2 && f3 && f4 && !f5 && f6 && f7){dec=9;flag=1;}//9
f1=!f1;
f2=!f2;
f3=!f3;
f4=!f4;
f5=!f5;
f6=!f6;
f7=!f7;
for(int f1_=0; f1_<=1; f1_++){
for(int f2_=0; f2_<=1; f2_++){
for(int f3_=0; f3_<=1; f3_++){
for(int f4_=0; f4_<=1; f4_++){
for(int f5_=0; f5_<=1; f5_++){
for(int f6_=0; f6_<=1; f6_++){
for(int f7_=0; f7_<=1; f7_++)
{
  pntr = 0;
  pcount++;
  lcd.setCursor(0,0);
  lcd.print("ReadPatterns:"); 
  lcd.print(pcount);
  lcd.setCursor(0,1);
  lcd.print("No Match Found"); 
  if((f1_==f1) && (f2_==f2) && (f3_==f3) && (f4_==f4) && (f5_==f5) && (f6_==f6) && !(f7_==f7))     {pntr=1; goto chk;} //0
  else if((f1_!=f1) && (f2_==f2) && (f3_==f3) && (f4_!=f4) && (f5_!=f5) && (f6_!=f6) && (f7_!=f7)) {pntr=1; goto chk;}//1
  else if((f1_==f1) && (f2_==f2) && !(f3_==f3) && (f4_==f4) && (f5_==f5) && !(f6_==f6) && (f7_==f7))                  {pntr=1; goto chk;}//2
  else if((f1_==f1) && (f2_==f2) && (f3_==f3) && (f4_==f4) && !(f5_==f5) && !(f6_==f6) && (f7_==f7))                   {pntr=1; goto chk;}//3
  else if(!(f1_==f1) && (f2_==f2) && (f3_==f3) && (f4_==f4) && !(f5_==f5) && (f6_==f6) && (f7_==f7))                  {pntr=1; goto chk;}//4
  else if((f1_==f1) && !(f2_==f2) && (f3_==f3) && (f4_==f4) && !(f5_==f5) && (f6_==f6) && (f7_==f7))                   {pntr=1; goto chk;}//5
  else if((f1_==f1) && !(f2_==f2) && (f3_==f3) && (f4_==f4) && (f5_==f5) && (f6_==f6) && (f7_==f7))                   {pntr=1; goto chk;}//6
  else if(!(f1_==f1) && !(f2_==f2) && (f3_==f3) && (f4_==f4) && (f5_==f5) && (f6_==f6) && (f7_==f7))                  {pntr=1; goto chk;}//6
  else if((f1_==f1) && (f2_==f2) && (f3_==f3) && (f4_!=f4) && (f5_!=f5) && (f6_!=f6) && (f7_!=f7))                {pntr=1; goto chk;}//7
  else if((f1_==f1) && (f2_==f2) && (f3_==f3) && (f4_==f4) && (f5_==f5) && (f6_==f6) && (f7_==f7))                    {pntr=1; goto chk;}//8
  else if((f1_==f1) && (f2_==f2) && (f3_==f3) && !(f4_==f4) && !(f5_==f5) && (f6_==f6) && (f7_==f7))                  {pntr=1; goto chk;}//9
  else if((f1_==f1) && (f2_==f2) && (f3_==f3) && (f4_==f4) && !(f5_==f5) && (f6_==f6) && (f7_==f7))                  {pntr=1; goto chk;}//9
  else pntr=0;
  //if((f1_!=f1) && (f2_!=f2) && (f3_!=f3) && (f4_!=f4) && (f5_!=f5) && (f6_!=f6) && (f7_!=f7)){pntr=1; goto chk;}
}}}}}}}
chk:
if(flag==1) 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Match At:"); 
  lcd.print(pcount);
  delay(2000);
  }
else
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("No Match Found"); 
  lcd.setCursor(0,1);
  lcd.print("PlzTrainPtrn");
  dec=-1;
  delay(2000);
}
}
void print_lcd(int num)
{
  lcd.clear();
  lcd.setCursor(0,0);
         lcd.print("RecognisedPattern:");
         lcd.setCursor(0,1);
  lcd.print(num);
}
