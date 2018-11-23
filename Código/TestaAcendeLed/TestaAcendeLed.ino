const int sel1= 6;
const int sel2= 7;
const int sel3= 8;
const int l1 = 2;
const int l2 = 3;
const int l3 = 4;

void select(int s){
  if (s==0){
    digitalWrite(sel1,LOW);
    digitalWrite(sel2,LOW);
    digitalWrite(sel3,LOW);
    
  }
  else if (s==1){
    digitalWrite(sel1,HIGH);
    digitalWrite(sel2,LOW);
    digitalWrite(sel3,LOW);
  }
  else if (s==2){
    digitalWrite(sel1,LOW);
    digitalWrite(sel2,HIGH);
    digitalWrite(sel3,LOW);
  }
  else if (s==3){
    digitalWrite(sel1,HIGH);
    digitalWrite(sel2,HIGH);
    digitalWrite(sel3,LOW);
  }
  else if (s==4){
    digitalWrite(sel1,LOW);
    digitalWrite(sel2,LOW);
    digitalWrite(sel3,HIGH);
  }
  else if (s==5){
    digitalWrite(sel1,HIGH);
    digitalWrite(sel2,LOW);
    digitalWrite(sel3,HIGH);
  }
  else if (s==6){
    digitalWrite(sel1,LOW);
    digitalWrite(sel2,HIGH);
    digitalWrite(sel3,HIGH);
  }
  else if (s==7){
    digitalWrite(sel1,HIGH);
    digitalWrite(sel2,HIGH);
    digitalWrite(sel3,HIGH);
  }
}

void select2(int s){
  if (s==0){
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(l3,LOW);
  }
  else if (s==1){
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(l3,LOW);
  }
  else if (s==2){
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,LOW);
  }
  else if (s==3){
    digitalWrite(l1,HIGH);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,LOW);
  }
  else if (s==4){
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(l3,HIGH);
  }
  else if (s==5){
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(l3,HIGH);
  }
  else if (s==6){
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,HIGH);
  }
  else if (s==7){
    digitalWrite(l1,HIGH);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,HIGH);
  }
}

  
void setup(){
  pinMode(sel1, OUTPUT);
  pinMode(sel2, OUTPUT);
  pinMode(sel3, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);    
}

void loop(){
  for(int i=0; i<8; i++){
    select(i);
    for(int j=0; j<8; j++){
     select2(j);
     delay(50);
    }
  }
}
