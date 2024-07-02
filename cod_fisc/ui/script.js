/****************************************************************************
**
** Copyright (C) 2006-2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
**
 *
 *
** This file is part of the project CodiceFiscale
**
** LGPLv3 License
**
**  You may use this file under the terms of the LGPLv3 license as follows:
*
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Codelinsoft and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/
//Funzione controllo codice fiscale
function readCodiceFiscale(testo)
{
    var s,mVal,setCF,setCF1,setCFPari,setCFDispari;
            
    if(testo.length == 0)
    {
        img.source = "qrc:/images/dialog-close.svg"
        label_text.text=qsTr("Errore: Non hai inserito nessun carattere o numero...")
    }
    
    if(testo.length != 16)
    {
        img.source = "qrc:/images/dialog-close.svg"
        label_text.text = qsTr("La lunghezza del codice fiscale non è\n"+
                                "corretta: il codice fiscale deve essere lungo\n"+
                                "esattamente 16 caratteri...")
    }
    
    mVal = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for(var i=0; i<16;i++)
    {
        if( mVal.indexOf( testo.charAt(i) ) == -1 ){
            img.source = "qrc:/images/dialog-close.svg"
            label_text.text = qsTr("Il codice fiscale contiene dei caratteri non validi:\n"+
                                    "i soli caratteri validi sono le lettere e le cifre.")
        }
    }
    
    setCF = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    setCF1 = "ABCDEFGHIJABCDEFGHIJKLMNOPQRSTUVWXYZ";
    setCFPari = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    setCFDispari = "BAKPLCQDREVOSFTGUHMINJWZYX";
    s = 0;
    for( var i = 1; i <= 13; i += 2 )
        s += setCFPari.indexOf( setCF1.charAt( setCF.indexOf( testo.charAt(i) )));
    for( var i = 0; i <= 14; i += 2 )
        s += setCFDispari.indexOf( setCF1.charAt( setCF.indexOf( testo.charAt(i) )));
    
    if(s%26 != testo.charCodeAt(15)-'A'.charCodeAt(0))
    {
        img.source = "qrc:/images/dialog-close.svg"
        label_text.text = qsTr("Il codice fiscale inserito non è corretto.\n"+
                                "Il codice di controllo non corrisponde.")
    }
    else
    {
        img.source = "qrc:/images/dialog-ok-apply.svg"
        label_text.text = qsTr("Il codice fiscale inserito è corretto.")
    }
}

//Funzione controllo partita iva
function controllaPIVA(piva)
{
    var i,s,c,numero;
    
    if( piva.length == 0 ){ 
        img_iva.source = "qrc:/images/dialog-close.svg";
        label_iva.text = qsTr("Errore: Non hai inserito nessun numero.")
    }

    if( piva.length != 11 )
    {
        img_iva.source = "qrc:/images/dialog-close.svg";
        label_iva.text = qsTr("La lunghezza della partita IVA non è\n"+
                               "corretta: la partita iva deve essere lunga\n"+
                               "esattamente 11 caratteri numerici")
    }

    numero = "0123456789";

    for( i = 0; i < 11; i++ ){ 
        if( numero.indexOf( piva.charAt(i) ) == -1 ){
            img_iva.source = "qrc:/images/dialog-close.svg";
            label_iva.text = qsTr("La lunghezza della partita IVA non è\n"+
                               "corretta: la partita iva deve essere lunga\n"+
                               "esattamente 11 caratteri numerici")
        }
    }

    s = 0;
    for( i = 0; i <= 9; i += 2 ){ 
        s += piva.charCodeAt(i) - '0'.charCodeAt(0);
    }
   
    for( i = 1; i <= 9; i += 2 ){ 
        c = 2*( piva.charCodeAt(i) - '0'.charCodeAt(0) );
        if( c > 9 ) c = c - 9;
            s += c;
    }

    if( ( 10 - s%10 )%10 != piva.charCodeAt(10) - '0'.charCodeAt(0)){
        img_iva.source = "qrc:/images/dialog-close.svg";
        label_iva.text = qsTr("La partita IVA non è valida:\n"+
                                  "il codice di controllo non corrisponde")
    }
    else{
        img_iva.source = "qrc:/images/dialog-ok-apply.svg"
        label_iva.text =qsTr("La partita iva è corretta.")
    }

}

//Funzione cancella tutto
function cancella()
{
    pageMain1.cognome.text=""
    pageMain1.nome.text=""
    pageMain1.maschio.checked=false
    pageMain1.femmina.checked=false
    pageMain1.combo.currentIndex=0
    pageMain1.combo_cm_st.currentIndex=0
    pageMain1.calendario.textDate.text=Qt.formatDate(new Date(),"dd/MM/yyyy")
    pageMain1.calcolo.text=""
}
//Calcolo del codice fiscale 
//Mesi
var mesi=['A','B','C','D','E','H','L','M','P','R','S','T']
//Controllo caratteri dispari
var controlloCaratteriDispari={
    0:1,  1:0,  2:5,  3:7,  4:9,  5:13, 6:15, 7:17, 8:19,
    9:21, A:1,  B:0,  C:5,  D:7,  E:9,  F:13, G:15, H:17,
    I:19, J:21, K:2,  L:4,  M:18, N:20, O:11, P:3,  Q:6, 
    R:8,  S:12, T:14, U:16, V:10, W:22, X:25, Y:24, Z:23
}
//Controllo caratteri pari
var controlloCaratteriPari={
    0:0,  1:1,   2:2,  3:3,   4:4,  5:5,  6:6,  7:7,  8:8,
    9:9,  A:0,   B:1,  C:2,   D:3,  E:4,  F:5,  G:6,  H:7,
    I:8,  J:9,   K:10, L:11,  M:12, N:13, O:14, P:15, Q:16,
    R:17, S:18,  T:19, U:20,  V:21, W:22, X:23, Y:24, Z:25
}
//Controllo carattere
var controlloCarattere = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

//Calcolo carattere di controllo
function calcolaCarattereDiControllo(codice_fiscale){
  var i,val=0
  for(i=0;i<15;i++){
    var c=codice_fiscale[i]
    if((i%2)==1)
      val+=controlloCaratteriPari[c]
    else
      val+=controlloCaratteriDispari[c]
  }
  val=val%26
  return controlloCarattere.charAt(val)
}
//Ottengo le consonanti
function Consonanti(str)
{
  return str.replace(/[^BCDFGHJKLMNPQRSTVWXYZ]/gi,'')
}
//Ottengo le vocali
function Vocali(str)
{
  return str.replace(/[^AEIOU]/gi,'')
}
//Calcolo cognome
function calcolaCodiceCognome(cognome)
{
  var codiceCognome=Consonanti(cognome)
  codiceCognome+=Vocali(cognome)
  codiceCognome+='XXX'
  codiceCognome=codiceCognome.substr(0,3)
  return codiceCognome.toUpperCase()
}
//Calcola nome
function calcolaCodiceNome(nome)
{
  var codiceNome=Consonanti(nome)
  if(codiceNome.length>=4){
    codiceNome=
      codiceNome.charAt(0)+
      codiceNome.charAt(2)+
      codiceNome.charAt(3)
  }else{
    codiceNome+=Vocali(nome)
    codiceNome+='XXX'
    codiceNome=codiceNome.substr(0,3)
  }
  return codiceNome.toUpperCase()
}
//Calcolo la data 
function calcolaData(gg,mm,aa,sesso)
{
  var d=new Date()
  d.setYear(aa);
  d.setMonth(mm-1);
  d.setDate(gg);
  var anno="0"+d.getFullYear()
  anno=anno.substr(anno.length-2,2);
  var mese=mesi[d.getMonth()]
  var giorno=d.getDate()
  if(sesso.toUpperCase()=='F') giorno+=40;
  giorno="0"+giorno
  giorno=giorno.substr(giorno.length-2,2);
  return ""+anno+mese+giorno
}
//Visualizzo il comune
function getComune(comune)
{
    var codiceComune;
    if(pageMain1.combo.currentIndex==0){
        pageMain2.mProvincia.text=m_model.setQueryModel("select provincia from paesi where paese='"+pageMain1.combo_cm_st.displayText+"'")
        codiceComune = m_model.setQueryModel("select cod_paese from paesi where paese='"+pageMain1.combo_cm_st.displayText+"'")
        pageMain2.mLuogoDiNascita.text=pageMain1.combo_cm_st.currentText
    }
    else if(pageMain1.combo.currentIndex==1){
        pageMain2.mProvincia.text=m_model1.setQueryModel("select provincia from stati where stato='"+pageMain1.combo_cm_st.displayText+"'")
        codiceComune = m_model1.setQueryModel("select cod_stato from stati where stato='"+pageMain1.combo_cm_st.displayText+"'")
        pageMain2.mLuogoDiNascita.text=pageMain1.combo_cm_st.currentText
    }
    return codiceComune;
}
//Visualizzo il codiceFiscale 
function calcolaCodiceFiscale(nome,cognome,sesso,day,month,year,paese)
{
    var codice=
        calcolaCodiceCognome(cognome)+calcolaCodiceNome(nome)+calcolaData(day.substr(0, 2),month.substr(3, 2),year.substr(6, 4),sesso)+getComune(paese)
        
    codice += calcolaCarattereDiControllo(codice);
    return codice;
}
