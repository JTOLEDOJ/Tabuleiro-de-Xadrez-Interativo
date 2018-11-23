const int sela = 6;
const int selb = 7;
const int selc = 8;
const int sel1 = 2;
const int sel2 = 3;
const int sel3 = 4;
int campo[8][8];
int linha;
char peca;
int coluna;
bool ok;
bool vezdobranco = true;
bool correto = false;
char linhac = '\0';
char colunac = '\0';
bool certo = false;
// Função que seleciona a linha do circuito de escrita. Recebe um inteiro de 0~7. Não retorna nada.

void SelectDemuxLinha(int s){
  if (s==0){
    digitalWrite(sela,LOW);
    digitalWrite(selb,LOW);
    digitalWrite(selc,LOW);
  }
  else if (s==1){
    digitalWrite(sela,HIGH);
    digitalWrite(selb,LOW);
    digitalWrite(selc,LOW);
  }
  else if (s==2){
    digitalWrite(sela,LOW);
    digitalWrite(selb,HIGH);
    digitalWrite(selc,LOW);
  }
  else if (s==3){
    digitalWrite(sela,HIGH);
    digitalWrite(selb,HIGH);
    digitalWrite(selc,LOW);
  }
  else if (s==4){
    digitalWrite(sela,LOW);
    digitalWrite(selb,LOW);
    digitalWrite(selc,HIGH);
  }
  else if (s==5){
    digitalWrite(sela,HIGH);
    digitalWrite(selb,LOW);
    digitalWrite(selc,HIGH);
  }
  else if (s==6){
    digitalWrite(sela,LOW);
    digitalWrite(selb,HIGH);
    digitalWrite(selc,HIGH);
  }
  else if (s==7){
    digitalWrite(sela,HIGH);
    digitalWrite(selb,HIGH);
    digitalWrite(selc,HIGH);
  }
}

// Função que seleciona a linha do circuito de escrita. Recebe um inteiro de 0~7. Não retorna nada.
void SelectDemuxColuna(int s){
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

// Função que acende os Leds. Recebe linha e coluna, setando os demux corretos.
void AcendeLed(int linha, int coluna){
  SelectDemuxLinha(linha);
  SelectDemuxColuna(coluna);
  //Serial.println("ACENDEU");
}

bool Movimenta(){
    
  // Movimentação do peão
  if(abs(campo[linha][coluna]) == 1){
    bool led[4];
    for(int i = 0; i < 4; i++) led[i]=0;
    int linhaaux = linha;
    int colunaaux = coluna;
    if(campo[linha][coluna] == 1){  // Peças brancas
      if(campo[linha+1][coluna] == 0 && campo[linha+2][coluna] == 0 && linha == 1) led[0]=1;
      if((linha+1) < 8){
        if(campo[linha+1][coluna] == 0) led[2]=1;
        if((coluna+1) < 8){
          if(campo[linha+1][coluna+1] < 0) led[3]=1;
        }
        if((coluna-1) >= 0){
          if(campo[linha+1][coluna-1] < 0) led[1]=1;
        }
      }
      //CETADOIDO!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      while (true){
        if(led[0] == 1) AcendeLed(linha+2, coluna);
        delay(10);
        if(led[1] == 1) AcendeLed(linha+1, coluna-1);
        delay(10);
        if(led[2] == 1) AcendeLed(linha+1, coluna);
        delay(10);
        if(led[3] == 1) AcendeLed(linha+1, coluna+1);
        delay(10);
        
        char c = Serial.read();
        
        if(c=='n'){
          break;
        }
        if (c=='y'){
          for (int i = 0; i<4; i++){
            if (led[i]==1) ok = true;
          }
          if (!ok){
            break;
          }
          else{
            Leitura2();
            AcendeLed(linha, coluna);
            if(led[0] == 1 && (linha == linhaaux+2 && coluna == colunaaux)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = 1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            if(led[1] == 1 && (linha == linhaaux+1 && coluna == colunaaux-1)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = 1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            if(led[2] == 1 && (linha == linhaaux+1 && coluna == colunaaux)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = 1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            if(led[3] == 1 && (linha == linhaaux+1 && coluna == colunaaux+1)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = 1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            Serial.println("MOVIMENTO ERRADO, TENTE DE NOVO");
            break;
          }
        }
      }
    }
    else{
      if(campo[linha-1][coluna] == 0 && campo[linha-2][coluna] == 0  && linha == 6) led[0]=1;
      if((linha-1) >= 0){
        if(campo[linha-1][coluna] == 0) led[2]=1;
        if((coluna-1) >= 0){
          if(campo[linha-1][coluna-1] > 0) led[3]=1;
        }
        if((coluna+1) < 8){
          if(campo[linha-1][coluna+1] > 0) led[1]=1;
        }
      }
      while (true){
        if(led[0] == 1) AcendeLed(linha-2, coluna);
        delay(10);
        if(led[1] == 1) AcendeLed(linha-1, coluna+1);
        delay(10);
        if(led[2] == 1) AcendeLed(linha-1, coluna);
        delay(10);
        if(led[3] == 1) AcendeLed(linha-1, coluna-1);
        delay(10);
        char c = Serial.read();
        if(c=='n'){
          break;
        }
        if (c=='y'){
          for (int i = 0; i<4; i++){
            if (led[i]==1) ok = true;
          }
          if (!ok){
            break;
          }
          else{
            Leitura2();
            AcendeLed(linha, coluna);
            if(led[0] == 1 && (linha == linhaaux-2 && coluna == colunaaux)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = -1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            if(led[1] == 1 && (linha == linhaaux-1 && coluna == colunaaux+1)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = -1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            if(led[2] == 1 && (linha == linhaaux-1 && coluna == colunaaux)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = -1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            if(led[3] == 1 && (linha == linhaaux-1 && coluna == colunaaux-1)){
              campo[linhaaux][colunaaux] = 0;
              campo[linha][coluna] = -1;
              Serial.println("Movimento Confirmado!");
              certo=true;
              break; 
            }
            Serial.println("MOVIMENTO ERRADO, TENTE DE NOVO");
            break;
          }
        }
      
     }
    }
  }

  // Movimentação da torre
  else if(abs(campo[linha][coluna]) == 2){
      bool achou = false;
      int l=0, r=0, u=0, d=0;
      
      for(int i = 1; (linha-i) >= 0; i++){
        if (campo[linha-i][coluna] != 0){
          d = i;
          achou = true;
        }
        if(achou) break;
        else d=i;
      }
      achou = false;
      
      for(int i = 1; (linha+i) <= 7; i++){
        if (campo[linha+i][coluna] != 0){
          u = i;
          achou = true;
        }
        if(achou) break;
        else u=i;
      }
      achou = false;
     
      for(int i = 1; (coluna + i) <= 7; i++){
        if (campo[linha][coluna+i] != 0){
          r = i;
          achou = true;
        }
        if(achou) break;
        else r=i;
      }
      achou = false;
      
      for(int i = 1; (coluna-i) >= 0; i++){
        if (campo[linha][coluna-i] != 0){
          l = i;
          achou = true;
        }
        if(achou) break;
        else l=i;
      }
      achou = false;
      while(true){
        for(int i = 1; i < d ; i++){
          if(linha-i > 0) AcendeLed(linha-i, coluna);
          delay(5);
        }
        if(campo[linha][coluna]*campo[linha-d][coluna] <= 0) AcendeLed(linha-d, coluna);
        delay(5);
        
        for(int i = 1; i < u; i++){
          if(linha+i < 7) AcendeLed(linha+i, coluna);
          delay(5);
        }
        if (campo[linha][coluna]*campo[linha+u][coluna] <= 0) AcendeLed(linha+u, coluna);
        delay(5);
        
        for(int i = 1; i < l; i++){
          if(coluna-i > 0) AcendeLed(linha, coluna-i);
          delay(5);
        }
        if(campo[linha][coluna]*campo[linha][coluna-l] <= 0) AcendeLed(linha, coluna-l);
        delay(5);
        
        for(int i = 1; i < r; i++){
          if(coluna + i < 7 ) AcendeLed(linha, coluna+i);
          delay(5);
        }
        if(campo[linha][coluna]*campo[linha][coluna+r] <= 0) AcendeLed(linha, coluna+r);
        delay(5);
        char c = Serial.read();
        if(c=='n'){
          break;
        }
        if (c=='y'){
          if (u == 0 && l == 0 && r == 0 && d ==0){
            break;
          }
          else{
            int linhaaux = linha;
            int colunaaux = coluna;
            Leitura2();
            AcendeLed(linha, coluna);
            if(linha<=linhaaux+u && coluna == colunaaux && linha >= linhaaux-d){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 2;
                if (!vezdobranco) campo[linha][coluna] = -2;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
            if(linha == linhaaux && coluna <= colunaaux+r && coluna >= coluna-l){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 2;
                if (!vezdobranco) campo[linha][coluna] = -2;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
            Serial.println("MOVIMENTO ERRADO, TENTE DE NOVO");
            break;
          }
        }
      }
    }
  
  // Movimentação do cavalo
  else if(abs(campo[linha][coluna]) == 3){
    bool led[8];
    for(int i = 0; i < 8; i++) led[i]=0;
    
    if((linha+2) < 8){
      if((coluna+1) < 8){
        if(campo[linha+2][coluna+1] != 0){
          if(campo[linha][coluna]*campo[linha+2][coluna+1] < 0) led[0]=1;
        }
        else led[0]=1;
      }
      
      if((coluna-1) >= 0){
        if(campo[linha+2][coluna-1] != 0){
          if(campo[linha][coluna]*campo[linha+2][coluna-1] < 0) led[1]=1;
        }
        else led[1]=1;
      }
    }
    
    if((linha-2) >= 0){
      if((coluna+1) < 8){
        if(campo[linha-2][coluna+1] != 0){
          if(campo[linha][coluna]*campo[linha-2][coluna+1] < 0) led[2]=1;
        }
        else led[2]=1;
      }
      
      if((coluna-1) >= 0){
        if(campo[linha-2][coluna-1] != 0){
          if(campo[linha][coluna]*campo[linha-2][coluna-1] < 0) led[3]=1;
        }
        else led[3]=1;
       }
    }
     
    if((coluna+2) < 8){
      if((linha+1) < 8){
        if(campo[linha+1][coluna+2] != 0){
          if(campo[linha][coluna]*campo[linha+1][coluna+2] < 0) led[4]=1;
        }
        else led[4]=1;
      }
      if((linha-1) > 0){
        if(campo[linha-1][coluna+2] != 0){
          if(campo[linha][coluna]*campo[linha-1][coluna+2] < 0) led[5]=1;
        }
        else led[5]=1;
      }
    }
    
    if((coluna-2) >= 0){
      if((linha+1) < 8){
        if(campo[linha+1][coluna-2] != 0){
          if(campo[linha][coluna]*campo[linha+1][coluna-2] < 0) led[6]=1;
        }
        else led[6]=1;
      }
      if((linha-1) > 0){
        if(campo[linha-1][coluna-2] != 0){
          if(campo[linha][coluna]*campo[linha-1][coluna-2] < 0) led[7]=1;
        }
        else led[7]=1;     
      }
    }
  
    while (true){
      if(led[0] == 1) AcendeLed(linha+2, coluna+1);
      delay(5);
      if(led[1] == 1) AcendeLed(linha+2, coluna-1);
      delay(5);
      if(led[2] == 1) AcendeLed(linha-2, coluna+1);
      delay(5);
      if(led[3] == 1) AcendeLed(linha-2, coluna-1);
      delay(5);
      if(led[4] == 1) AcendeLed(linha+1, coluna+2);
      delay(5);
      if(led[5] == 1) AcendeLed(linha-1, coluna+2);
      delay(5);
      if(led[6] == 1) AcendeLed(linha+1, coluna-2);
      delay(5);
      if(led[7] == 1) AcendeLed(linha-1, coluna-2);
      delay(5);
      
      char c = Serial.read();
      if(c=='n'){
          break;
        }
      if(c== 'y'){
        int colunaaux = coluna;
        int linhaaux = linha;
        Leitura2();
        AcendeLed(linha, coluna);
        if(led[0] == 1 && linha == linhaaux+2 && coluna == colunaaux+1){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        if(led[1] == 1 && linha == linhaaux+2 && coluna == colunaaux-1){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        if(led[2] == 1 && linha == linhaaux-2 && coluna == colunaaux+1){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        if(led[3] == 1 && linha == linhaaux-2 && coluna == colunaaux-1){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        if(led[4] == 1 && linha == linhaaux+1 && coluna == colunaaux+2){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        if(led[5] == 1 && linha == linhaaux-1 && coluna == colunaaux+2){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        if(led[6] == 1 && linha == linhaaux+1 && coluna == colunaaux-2){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        if(led[7] == 1 && linha == linhaaux-1 && coluna == colunaaux-2){
          campo[linhaaux][colunaaux]=0;
          if(vezdobranco) campo[linha][coluna]=3;
          if(!vezdobranco) campo[linha][coluna]=-3;
          Serial.println("Movimento Confirmado!");
          certo=true;
          break;
        }
        Serial.println("MOVIMENTO ERRADO, TENTE DE NOVO");
        break;
      }
    }
  }

  // Movimentação do bispo
  else if(abs(campo[linha][coluna]) == 4){
    bool achou = false;
    int ld=0, lu=0, rd=0, ru=0;
    
    for(int i = 1; (linha-i >= 0 && coluna-i >= 0); i++){
      if(campo[linha-i][coluna-i] != 0){
        ld = i;
        achou = true;
      }
      if(achou) break;
      else ld=i;
    }
    achou = false;
    
    for(int i = 1; (linha+i <= 7 && coluna-i >= 0); i++){
      if(campo[linha+i][coluna-i] != 0){
        lu = i;
        achou = true;
      }
      if (achou) break;
      else lu=i;
    }
    achou = false;
    
    for(int i = 1; (linha+i <= 7 && coluna+i <= 7); i++){
      if(campo[linha+i][coluna+i] != 0){
        ru = i;
        achou = true;
      }
      if (achou) break;
      else ru=i;
    }
    achou = false;
    for (int i = 1; (linha-i >= 0 && coluna+i <= 7); i++){
      if (campo[linha-i][coluna+i] != 0){
        rd = i;
        achou = true;
      }
      if (achou) break;
      else rd=i;
    }
    achou = false;
    
    while(true){
      //Serial.println(lu);
      //Serial.println(ld);
      //Serial.println(ru);
      //Serial.println(rd);
      for(int i = 1; i < lu ; i++){
        if (linha+i < 8 && coluna-i >= 0) AcendeLed(linha+i, coluna-i);
        delay(5);
        //Serial.println("Acende, porra!");
      }
      if(campo[linha][coluna]*campo[linha-lu][coluna+lu] <= 0) AcendeLed(linha + lu, coluna - lu);
      delay(5);
      
      for(int i = 1; i < ru; i++){
        if(linha + i < 8 && coluna + i < 8 ) AcendeLed(linha + i, coluna + i);
        delay(5);
      }
      if(campo[linha][coluna]*campo[linha+ru][coluna+ru] <= 0) AcendeLed(linha + ru, coluna + ru);
      delay(5);
      
      for(int i = 1; i < ld; i++){
        if(linha-i >= 0 && coluna-i >= 0 ) AcendeLed(linha-i, coluna-i);
        delay(5);

      }
      if(campo[linha][coluna]*campo[linha-ld][coluna-ld] <= 0) AcendeLed(linha-ld, coluna-ld);
      delay(5);
      for(int i = 1; i < rd; i++){
        if(linha - i >= 0 && coluna + i < 8 ) AcendeLed(linha - i, coluna + i);
        delay(5);
      }
      if(campo[linha][coluna]*campo[linha-rd][coluna+rd] <= 0) AcendeLed(linha - rd, coluna + rd);
      delay(5);
      char c = Serial.read();
      if(c=='n'){
          break;
      }
      if (c=='y'){
        
          if (rd == 0 && ld == 0 && ru == 0 && lu ==0){
            break;
          }
          else{
            int linhaaux = linha;
            int colunaaux = coluna;
            Leitura2();
            AcendeLed(linha, coluna);
            int teste1 = abs(linhaaux-linha);
            int teste2 = abs(colunaaux-coluna);
            
            while (teste1!=teste2){
              Leitura2();
              AcendeLed(linha, coluna);
              teste1 = abs(linhaaux-linha);
              teste2 = abs(colunaaux-coluna);  
            }
            
            if(linha<=linhaaux+ru && coluna<=colunaaux+ru && linha >= linhaaux-ld && coluna >= colunaaux-ld){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 4;
                if (!vezdobranco) campo[linha][coluna] = -4;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
            if(linha >= linhaaux-rd && coluna <= colunaaux+rd && linha <= linhaaux+lu && coluna >= colunaaux-lu){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 4;
                if (!vezdobranco) campo[linha][coluna] = -4;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
         
            Serial.println("MOVIMENTO ERRADO, TENTE DE NOVO");
            break;
            }
       }
     }
   }

  // Movimentação da rainha
  else if(abs(campo[linha][coluna]) == 5){
    bool achou = false;
    int ld=0, lu=0, rd=0, ru=0, l=0, r=0, u=0, d=0;

    // Movimentação em diagonal
    for(int i = 1; (linha-i >= 0 && coluna-i >= 0); i++){
      if(campo[linha-i][coluna-i] != 0){
        ld = i;
        achou = true;
      }
      if(achou) break;
      else ld = i;
    }
    achou = false;
    
    for(int i = 1; (linha+i <= 7 && coluna-i >= 0); i++){
      if(campo[linha+i][coluna-i] != 0){
        lu = i;
        achou = true;
      }
      if (achou) break;
      else lu = i;
    }
    achou = false;
    
    for(int i = 1; (linha+i <= 7 && coluna+i <= 7); i++){
      if(campo[linha+i][coluna+i] != 0){
        ru = i;
        achou = true;
      }
      if (achou) break;
      else ru = i;
    }
    achou = false;
    for (int i = 1; (linha-i >= 0 && coluna+i <= 7); i++){
      if (campo[linha-i][coluna+i] != 0){
        rd = i;
        achou = true;
      }
      if (achou) break;
      else rd = i;
    }
    achou = false;
    // Movimentação em horizontal e vertical
   
    for(int i = 1; (linha+i) <= 7; i++){
      if (campo[linha+i][coluna] != 0){
        u = i;
        achou = true;
      }
      if(achou) break;
      else u = i;
    }
    achou = false;

    for(int i = 1; (linha-i) >= 0; i++){
      if (campo[linha-i][coluna] != 0){
        d = i;
        achou = true;
      }
      if(achou) break;
      else d = i;
    }
    achou = false;
    
    for(int i = 1; (coluna + i) <= 7; i++){
      if (campo[linha][coluna+i] != 0){
        r = i;
        achou = true;
      }
      if(achou) break;
      else r = i;
    }
    achou = false;
    
    for(int i = 1; (coluna-i) >= 0; i++){
      if (campo[linha][coluna-i] != 0){
        l = i;
        achou = true;
      }
      if(achou) break;
      else l = i;
    }
    achou = false;
    
    while(true){
     char c = Serial.read();
      if(c=='n'){
          break;
        }
      if (c=='y'){
          if (rd == 0 && ld == 0 && ru == 0 && lu == 0 && r == 0 && d == 0 && u == 0 && l ==0){
            break;
          }
          
          else{
            int linhaaux = linha;
            int colunaaux = coluna;
            Leitura2();
            AcendeLed(linha, coluna);
           
 
            if(linha<=linhaaux+u && coluna == colunaaux && linha >= linhaaux-d){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 5;
                if (!vezdobranco) campo[linha][coluna] = -5;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
            if(linha == linhaaux && coluna <= colunaaux+r && coluna >= coluna-l){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 5;
                if (!vezdobranco) campo[linha][coluna] = -5;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
            
            if(linha<=linhaaux+ru && coluna<=colunaaux+ru && linha >= linhaaux-ld && coluna >= colunaaux-ld){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 5;
                if (!vezdobranco) campo[linha][coluna] = -5;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
            if(linha >= linhaaux-rd && coluna <= colunaaux+rd && linha <= linhaaux+lu && coluna >= colunaaux-lu){
              if ((campo[linhaaux][colunaaux])*(campo[linha][coluna])<=0){
                campo[linhaaux][colunaaux] = 0;
                if (vezdobranco) campo[linha][coluna] = 5;
                if (!vezdobranco) campo[linha][coluna] = -5;
                Serial.println("Movimento Confirmado!");
                certo=true;
                break;
              } 
            }
         Serial.println("MOVIMENTO ERRADO, TENTE DE NOVO");
         break;   
         }
       }
      
      
      
      // Movimentação em diagonal
      
      
      for(int i = 1; i < lu ; i++){
        if (linha+i < 8 && coluna-i >= 0) AcendeLed(linha+i, coluna-i);
        delay(5);
        //Serial.println("Acende, porra!");
      }
      if(campo[linha][coluna]*campo[linha+lu][coluna-lu] <= 0) AcendeLed(linha + lu, coluna - lu);
      delay(5);
      
      for(int i = 1; i < ru; i++){
        if(linha + i < 8 && coluna + i < 8 ) AcendeLed(linha + i, coluna + i);
        delay(5);
      }
      if(campo[linha][coluna]*campo[linha+ru][coluna+ru] <= 0) AcendeLed(linha + ru, coluna + ru);
      delay(5);
      
      for(int i = 1; i < ld; i++){
        if(linha-i >= 0 && coluna-i >= 0 ) AcendeLed(linha-i, coluna-i);
        delay(5);
;
      }
      if(campo[linha][coluna]*campo[linha-ld][coluna-ld] <= 0) AcendeLed(linha-ld, coluna-ld);
      delay(5);
      
      
      for(int i = 1; i < rd; i++){
        if(linha - i >= 0 && coluna + i < 8 ) AcendeLed(linha - i, coluna + i);
        delay(5);
        
      }
      if(campo[linha][coluna]*campo[linha-rd][coluna+rd] <= 0) AcendeLed(linha - rd, coluna + rd);
      delay(5);
      
      // Movimentação em horizontal e vertical
      for(int i = 1; i < d ; i++){
          if(linha-i > 0) AcendeLed(linha-i, coluna);
          delay(5);
        }
        if(campo[linha][coluna]*campo[linha-d][coluna] <= 0) AcendeLed(linha-d, coluna);
        delay(5);
        
        for(int i = 1; i < u; i++){
          if(linha+i < 7) AcendeLed(linha+i, coluna);
          delay(5);
        }
        if (campo[linha][coluna]*campo[linha+u][coluna] <= 0) AcendeLed(linha+u, coluna);
        delay(5);
        
        for(int i = 1; i < l; i++){
          if(coluna-i > 0) AcendeLed(linha, coluna-i);
          delay(5);
        }
        if(campo[linha][coluna]*campo[linha][coluna-l] <= 0) AcendeLed(linha, coluna-l);
        delay(5);
        
        for(int i = 1; i < r; i++){
          if(coluna + i < 7 ) AcendeLed(linha, coluna+i);
          delay(5);
        }
        if(campo[linha][coluna]*campo[linha][coluna+r] <= 0) AcendeLed(linha, coluna+r);
        delay(5);
    }
  }

  // Movimentação do rei
  else if(abs(campo[linha][coluna]) == 6){
    bool led[8];
    for (int i = 0; i<8;i++){
      led[i]=false;
    }
   while(true){
    if(coluna < 7){
      if(campo[linha][coluna+1]*campo[linha][coluna] <= 0){
        AcendeLed(linha, coluna+1);
        led[0] = true;
      }
    }
    if(linha < 7 && coluna < 7){
      if(campo[linha+1][coluna+1]*campo[linha][coluna] <= 0){
        AcendeLed(linha+1, coluna+1);
        led[1] = true;
      }
    }
    if(linha < 7){
      if(campo[linha+1][coluna]*campo[linha][coluna] <= 0){
        AcendeLed(linha+1, coluna);
        led[2] = true;
      }
    }
    if(linha < 7 && coluna > 0){
      if(campo[linha+1][coluna-1]*campo[linha][coluna] <= 0){
        AcendeLed(linha+1, coluna-1);
        led[3] = true;
      }
    }
    if(coluna > 0){
      if(campo[linha][coluna-1]*campo[linha][coluna] <= 0){
        AcendeLed(linha, coluna-1);
        led[4] = true;
      }
    }
    if(linha > 0 && coluna > 0){
      if(campo[linha-1][coluna-1]*campo[linha][coluna] <= 0){
        AcendeLed(linha-1, coluna-1);
        led[5] = true;
      }
    }
    if(linha > 0){
      if(campo[linha-1][coluna]*campo[linha][coluna] <= 0){
        AcendeLed(linha-1, coluna);
        led[6] = true;
      }
    }
    if(linha > 0 && coluna < 7){
      if(campo[linha-1][coluna+1]*campo[linha][coluna] <= 0) AcendeLed(linha-1, coluna+1);
      led[7] = true;
    }
    char c = Serial.read();
    if(c=='n'){
          break;
        }
     if(c=='y'){
      int colunaaux = coluna;
      int linhaaux = linha;
      Leitura2();
      AcendeLed(linha, coluna);
      if (led[0] && coluna == colunaaux+1 && linha == linhaaux){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        Serial.println("Movimento Confirmado!");
        certo=true;
        break;
      }
      if (led[1] && coluna == colunaaux+1 && linha == linhaaux+1){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        Serial.println("Movimento Confirmado!");
        certo=true;
        break;
      }
      if (led[2] && coluna == colunaaux && linha == linhaaux+1){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        Serial.println("Movimento Confirmado!");
        certo=true;
        break;
      }
      if (led[3] && coluna == colunaaux-1 && linha == linhaaux+1){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        Serial.println("Movimento Confirmado!");
        certo=true;
        break;
      }
      if (led[4] && coluna == colunaaux-1 && linha == linhaaux){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        certo=true;
        Serial.println("Movimento Confirmado!");
        break;
      }
      if (led[5] && coluna == colunaaux-1 && linha == linhaaux-1){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        Serial.println("Movimento Confirmado!");
        certo=true;
        break;  
      }
      if (led[6] && coluna == colunaaux && linha == linhaaux-1){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        Serial.println("Movimento Confirmado!");
        certo=true;
        break;
      }
      if (led[7] && coluna == colunaaux+1 && linha == linhaaux-1){
        campo[linhaaux][colunaaux] = 0;
        if(vezdobranco) campo[linha][coluna]=6;
        if(!vezdobranco) campo[linha][coluna]=-6;
        Serial.println("Movimento Confirmado!");
        certo=true;
        break;
      }
      Serial.println("MOVIMENTO ERRADO, TENTE DE NOVO");
      break;
            
    }
  }
 }
}
void Inicio(){
  for(int i = 0; i < 8; i++){
    if(i == 0){
      campo[i][0] = 2;
      campo[i][7] = 2;
      campo[i][1] = 3;
      campo[i][6] = 3;
      campo[i][2] = 4;
      campo[i][5] = 4;
      campo[i][3] = 6;
      campo[i][4] = 5;
      // Seta as torres, bispos, etc... Brancos
    }
    if(i == 1){
      for (int j = 0; j < 8; j++){
        campo[i][j] = 1; // Seta os peões brancos
      }
    }

    if(i >= 2 && i <=5){
      campo[i][0] = 0;
      campo[i][1] = 0;
      campo[i][2] = 0;
      campo[i][3] = 0;
      campo[i][4] = 0;
      campo[i][5] = 0;
      campo[i][6] = 0;
      campo[i][7] = 0; 
    }
    if (i == 6){
      for (int j = 0; j < 8; j++){
        campo[i][j] = -1; // Seta os peões pretos
      }
    }
    if (i == 7){
      campo[i][0] = -2;
      campo[i][7] = -2;
      campo[i][1] = -3;
      campo[i][6] = -3;
      campo[i][2] = -4;
      campo[i][5] = -4;
      campo[i][3] = -6;
      campo[i][4] = -5;
      //Seta as torres, bispos, etc... Pretos
    }
  }
}

void TestaLED(){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      AcendeLed(i, j);
      delay(40);
    }
  }
}

void setup(){
  // linhas são selecionadas por letras e colunas por números
  pinMode(sela, OUTPUT);
  pinMode(selb, OUTPUT);
  pinMode(selc, OUTPUT);
  pinMode(sel1, OUTPUT);
  pinMode(sel2, OUTPUT);
  pinMode(sel3, OUTPUT);
  TestaLED();
  Inicio();
  Serial.begin(9600);
  
}

void TrocaLinha(){
  correto = true;
  if(linhac == 'a') linha = 0;
  else if(linhac == 'b') linha = 1;
  else if(linhac == 'c') linha = 2;
  else if(linhac == 'd') linha = 3;
  else if(linhac == 'e') linha = 4;
  else if(linhac == 'f') linha = 5;
  else if(linhac == 'g') linha = 6;
  else if(linhac == 'h') linha = 7;
  else{
    correto = false;
    Serial.println("Linha não reconhecida. Verifique e Digite Novamente");
    Serial.println("Digite a linha da peça: a, b, c, d, e, f, g, h");  
    linhac = '\0'; 
   }
}

void TrocaColuna(){
  correto = true;
  if(colunac == '1') coluna = 0;
  else if(colunac == '2') coluna = 1;
  else if(colunac == '3') coluna = 2;
  else if(colunac == '4') coluna = 3;
  else if(colunac == '5') coluna = 4;
  else if(colunac == '6') coluna = 5;
  else if(colunac == '7') coluna = 6;
  else if(colunac == '8') coluna = 7;
  else{
    correto = false;
    Serial.println("Coluna não reconhecida. Verifique e Digite Novamente");
    Serial.println("Digite a coluna da peça: 1, 2, 3, 4, 5, 6, 7, 8");  
    colunac = '\0'; 
   }
}

void Leitura(){
  Serial.println("Digite a linha da peça: a, b, c, d, e, f, g, h");
  while(!correto){
    while(Serial.available()>0){
      linhac = Serial.read();  
      Serial.println(linhac);
      delay(100);
    }
    if(linhac!='\0') TrocaLinha();
  }
  correto = false;
  
  delay(500);
  Serial.println("Digite a coluna da peça: 1, 2, 3, 4, 5, 6, 7, 8");
  while (!correto){
    while(Serial.available()>0){
      colunac = Serial.read();
      Serial.println(colunac);
      delay(100);
    }
    if(colunac!='\0') TrocaColuna();
  }
  correto = false;
  colunac='\0';
  linhac='\0';
}

void Leitura2(){
  Serial.println("Digite a linha pra onde quer mover: a, b, c, d, e, f, g, h");
  while(!correto){
    while(Serial.available()>0){
      linhac = Serial.read();  
      Serial.println(linhac);
      delay(100);
    }
    if(linhac!='\0') TrocaLinha();
  }
  correto = false;
  
  delay(500);
  Serial.println("Digite a coluna pra onde quer mover: 1, 2, 3, 4, 5, 6, 7, 8");
  while (!correto){
    while(Serial.available()>0){
      colunac = Serial.read();
      Serial.println(colunac);
      delay(100);
    }
    if(colunac!='\0') TrocaColuna();
  }
  correto = false;
  colunac='\0';
  linhac='\0';
}

void loop(){
  bool achou = false;
  if(vezdobranco) Serial.println("Vez do Branco");
  else Serial.println("Vez do Preto");
  
  Leitura();
  while(!achou){
    achou = true;
    while(campo[linha][coluna] == 0){
      Serial.println("Peça não encontrada! Verifique linha e coluna!");
      Leitura();
      achou = false;
    }
    while(vezdobranco && campo[linha][coluna] < 0){
      Serial.println("Opa, peça do adversário. Tente de novo");
      Leitura();
      achou = false;
    }
    while(!vezdobranco && campo[linha][coluna] > 0){
      Serial.println("Opa, peça do adversário. Tente de novo");
      Leitura();
      achou = false;
    }
  }
  if(achou){
    if (abs(campo[linha][coluna])==1) Serial.println("Peao"); 
    if (abs(campo[linha][coluna])==2) Serial.println("Torre"); 
    if (abs(campo[linha][coluna])==3) Serial.println("Cavalo"); 
    if (abs(campo[linha][coluna])==4) Serial.println("Bispo"); 
    if (abs(campo[linha][coluna])==5) Serial.println("Rainha"); 
    if (abs(campo[linha][coluna])==6) Serial.println("Rei"); 
    Serial.println("Digite y para confirmar o movimento e n para mexer outra peça");
    Movimenta();
  }

  if(certo){
  if(vezdobranco) vezdobranco = false;
  else vezdobranco = true;
  certo=false;
  }
}
