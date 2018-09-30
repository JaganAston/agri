#define dht11_pin 14 //Analog port 0 on Arduino Uno
byte read_dht11_dat()
{
byte i = 0;
byte result=0;
for(i=0; i< 8; i++)
{
while (!digitalRead(dht11_pin));
delayMicroseconds(30);
if (digitalRead(dht11_pin) != 0 )
bitSet(result, 7-i);
while (digitalRead(dht11_pin));
}
return result;
}
int threshold=400;
void setup()
{
pinMode(dht11_pin, OUTPUT);
digitalWrite(dht11_pin, HIGH);
Serial.begin(9600);
Serial.println("Ready");
}

void loop()    
{
byte dht11_dat[5];   
byte dht11_in;
byte i;// start condition

digitalWrite(dht11_pin, LOW);
delay(18);
digitalWrite(dht11_pin, HIGH);
delayMicroseconds(1);
pinMode(dht11_pin, INPUT);
delayMicroseconds(40);     

if (digitalRead(dht11_pin))
{
Serial.println("dht11 start condition 1 not met"); // wait for DHT response signal: LOW
delay(1000);
return;
}
delayMicroseconds(80);
if (!digitalRead(dht11_pin))
{
Serial.println("dht11 start condition 2 not met");  //wair for second response signal:HIGH
return;
}

delayMicroseconds(80);// now ready for data reception
for (i=0; i<5; i++)
{  dht11_dat[i] = read_dht11_dat();}  //recieved 40 bits data. Details are described in datasheet

pinMode(dht11_pin, OUTPUT);
digitalWrite(dht11_pin, HIGH);
byte dht11_check_sum = dht11_dat[0]+dht11_dat[2];// check check_sum

int cu=dht11_dat[0]; //humidity value
int du=dht11_dat[2]; //temperatue value
delay(2000); //fresh time
int sensorValue = analogRead(A1);
delay(10000); 
  Serial.print("MOISTURE LEVEL:");
  Serial.print(sensorValue);
  Serial.print("\n");
  
  if(sensorValue<threshold)
  {
    printSoilChoice2();
       }
       else{
        printSoilChoice();
        delay(1000);
        }
 Serial.print("\n SELECT THE CROP ");
      delay(10000);
     int  ch;
     ch = Serial.read();
     Serial.print("\n \n your choice \n");
       switch(ch)
       {
        case '1':
        Serial.print("COTTON \n");
        delay(1000);
        Serial.print("Germination phase:(1-15 days) \n");
        Serial.print("Vegitative phase:(16-44 days) \n");
        Serial.print("Flowering phase:(45-100 days for hybride, 87 days for varieties) \n");
        Serial.print("N: 60-100kg/ha,P&K doses are as per test \n");
        Serial.print("CENTRAL COTTON ZONE:\n");
        Serial.print("N:P:K 40-20-20,50-25-25, 80-40-40 for varieties \n");
        Serial.print("N:P:K 100-50-50, 160-80-80, 240-120-120 for hybrids \n");
        delay(1000);
        Serial.print("SOUTHERN COTTON ZONE:\n");
        Serial.print("N:P:K 40-20-20, 60-30-30, 90-45-45 for varieties \n");
        Serial.print("N:P:K 100-50-50, 120-60-60, 150-60-60 for hybrids \n");
       break;
        case '2':
          Serial.print("PULSES  \n");
          Serial.print("Vrieties:Blackgram,Greengram,Cowpea,Redgram,Soybean,Field Lab Lab,Garden Lab Lab \n");
        break;
          case '3':
          Serial.print("SUGAR CANE  \n");
          delay(1000);
            Serial.print(" Total Growth phase:(270-365 days)");
            Serial.print("Recommended N&K Value: \n");
            Serial.print("275 and 112.5kg/ha(15 DAYS interval)  \n");
            Serial.print("N:25kg/ha/split, K2O:8kg/ha/split  \n");
            Serial.print("Fertigation up to 210 DAP also RECOMMENDABLE");
         break;
            case '4':
              Serial.print("JUTE");
              delay(1000);
         break;
         case '5':
         Serial.print("MAIZE \n");
         delay(1000);
         Serial.print("Germination phase: 1-14 days \n");
         Serial.print("Vegitation phase: 15-39 days \n");
         Serial.print("Flowering phase:40-65 days \n");
         Serial.print("Maturity phase:66-95 days \n");
         Serial.print("FERTIGATION SCHEDULE FOR HYBRID VARIETY: \n");
         Serial.print("DAP: 18-46-0(5.00/ha/day),UREA:46-0-0(2.50/ha/day)(6-25DAYS) \n");
         Serial.print("DAP: 18-46-0(1.86/ha/day),UREA:46-0-0(4.29/ha/day),MOP:0-0-60(2.14/ha/day)(26-60DAYS) \n");
         Serial.print("UREA:46-0-0(4.13/ha/day),MOP:0-0-60(3.33/ha/day)(61-75DAYS) \n");
         break;
         case '6':
         Serial.print("MILLET \n");
         Serial.print("MILLET VARIETIES \n");
         Serial.print("MAIZE, SORGHUM, RAGI, CUMBU \n");
         break;
         case '7':
         Serial.print("BARLEY \n");
         Serial.print("Total Growth Phase:(120-150days) \n");
         Serial.print("NUTRITION \n");
         Serial.print("Calories: 352 \n");
         Serial.print("RICH SOURCE \n");
         Serial.print("Essential nutrients(20%DV),Protein,Dietary fiber,B Vitamins, Niacin(31%DV) \n");
         Serial.print("Vitamin B6(20%DV) \n");
         Serial.print("Manganese(63%DV) \n");
         Serial.print("Phosphorus(32%DV) \n");
         Serial.print("Carbohydrates(78%), Fat(1%), Protein(10%),Water(10%) \n");
         break;
         default:
          Serial.print("none");
          }
delay(100000);
}

void printSoilChoice(){
       Serial.print("SANDY SOIL:");
Serial.print("\n");
  Serial.print("5.maize");
  Serial.print("\n");
  Serial.print("6.millet");
  Serial.print("\n");
  Serial.print("7.Barley");
        }
void printSoilChoice2() 
{
  Serial.print("SOIL TUPE:");
  delay(1000);
Serial.print("LOAMY SOIL \n ");
  delay(1000);
  Serial.print("THE CROP CAN BE CULTIVATED IN YOUR LAND:  \n");
    Serial.print("1.Cotton \n");
     Serial.print("2.Pulses \n");
      Serial.print("3.Sugarcane \n");
       Serial.print("4.Jute \n");
       
}

