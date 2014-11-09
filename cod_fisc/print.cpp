/****************************************************************************
**
** Copyright (C) 2006-2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
**
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
#include "print.h"

print::print()
{
       // Creazione oggetto printer (puntatore)
       // ed impostazioni varie sul formato pagina, nome file di appoggio
       // formato file prodotto
       // impostazione margine e risoluzione
       printer = new QPrinter();
       // Formato A4 = 210*297 millimetri
       // Formato A4 = 210*297 millimetri

       printer->setPageMargins(5.0,5.0,5.0,5.0,QPrinter::Millimeter);
       printer->setPaperSize(QPrinter::A2);
       #ifdef Q_OS_LINUX
       printer->setOutputFormat(QPrinter::PdfFormat);
       #endif
       #ifdef Q_OS_MAC
       printer->setOutputFormat(QPrinter::PdfFormat);
       #endif
       printer->setResolution(254);
       // Formato A4 = millimetri 210*297
       // un pollice = 25,4 millimetri
       // risoluzione posta a 254 punti per pollice
       // quindi 10 punti = 1 millimetro
       stampaDlg = new QPrintDialog();
       stampaDlg->setEnabledOptions(QAbstractPrintDialog::PrintPageRange);

       //Creazione oggetto painter che servirÃ  per disegnare le cose
       painter = new QPainter();
}

void print::print_codice(QPrinter *printer, QImage img, QString cognome, QString nome,
                         bool maschio, bool femmina, QString com_st, QString pr_st, QString codice, QDate date)
{
        printer->setPaperSize(QPrinter::A2);
        printer->setOrientation(QPrinter::Landscape);
        printer->setResolution(254);

           //printer->setOrientation(QPrinter::Landscape);
         // inizio fase di stampa. Si attiva il painter sulla printer
         // impostata in precedenza
      painter->begin(printer);

      painter->drawImage(5,5,img);
      painter->setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
      painter->drawText(60,190,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,codice);
      painter->drawText(30,240,480,100, Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,cognome);
      painter->drawText(30,290,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap, nome);
      painter->drawText(40,340,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap, com_st);
      painter->drawText(40,395,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,pr_st);
      painter->drawText(30,450,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,date.toString(QString("dd/MM/yyyy")));

      if(maschio){
          painter->drawText(480,335,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,"M");
      }
      else if(femmina){
          painter->drawText(480,335,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,"F");
      }
      painter->setFont(QFont("Arial",12,50));
      painter->drawText(400,440,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,"FAC SIMILE");
      painter->end();
}
