/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "saveimage.h"
#include <QFileDialog>

SaveImage::SaveImage(QQuickItem *parent) : QQuickItem(parent)
{
    
}

void SaveImage::saveImages(QQuickItem *item)
{
    auto grabResult = item->grabToImage();
    
    /*
     * Bug presente nell'apertura della finestra di dialogo
     * su ubuntu e kubuntu
     */
    QString fileName;
    QStringList file_name;

    QFileDialog dialog(0);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setWindowTitle(tr("Esporta immagine"));
    dialog.setNameFilter(tr("Images (*.png);;Tutti i file(*.*);;PNG(*.png)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
      if(dialog.exec())
 file_name = dialog.selectedFiles();
 
    if (grabResult) {
      foreach (fileName, file_name) {

 if (fileName.length() != 0) {
     // Aggiunge estensione alla fine del file se non c'è
     if (fileName.indexOf(".png") < 0) {
  fileName += ".png";
     }
 }

 if(!fileName.isNull()){
  grabResult->saveToFile(fileName);
 } else {
     QMessageBox::warning(0,tr("CodiceFiscale"),tr("Impossibile salvare l'immagine"));
 }
      }
    }
}

void SaveImage::exportPdf()
{
 QString fileName;
 QStringList nomeFile;
 //FIXME
 /*
  * Bug presente nell'apertura della finestra di dialogo
  * su ubuntu e kubuntu
  */
 QFileDialog dialog(0);
 dialog.setFileMode(QFileDialog::AnyFile);
 dialog.setWindowTitle(tr("Esporta in PDF"));
 dialog.setNameFilter(tr("Pdf Files(*.pdf);;Tutti i file(*.*)"));
 dialog.setViewMode(QFileDialog::Detail);
 dialog.setAcceptMode(QFileDialog::AcceptSave);
 if(dialog.exec())
#if QT_VERSION >= 0x050000
 nomeFile = dialog.selectedFiles();
#else
nomeFile << dialog.selectedFiles();
#endif

 foreach (fileName, nomeFile) {

 if (fileName.length() != 0) {
  // Aggiunge estensione alla fine del file se non c'è
  if (fileName.indexOf(".pdf") < 0) {
      fileName += ".pdf";
  }
     }
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);

    /*
     *FIXME Processo di stampa
     */
    Q_UNUSED(printer);

    printer->setPageSize(QPrinter::A7);
    printer->setOutputFileName(fileName);
    QImage image_800x600 = QImage(":/images/codicefiscale_800x600.png");
    printer->setOrientation(QPrinter::Landscape);
    printer->setResolution(254);

     QPainter *painter = new QPainter(printer);

     painter->drawImage(5,5,image_800x600);
     painter->setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
     painter->drawText(60,190,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getCodice());
     painter->drawText(30,240,480,100, Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getSurname());
     painter->drawText(30,290,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap, getName());
     painter->drawText(40,340,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap, getComuneStato());
     painter->drawText(40,395,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getProvincia());
     painter->drawText(30,450,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getData());
     painter->drawText(480,335,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getSesso());
     painter->setFont(QFont("Arial",12,50));
     painter->drawText(400,440,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,"FAC SIMILE");
     painter->end();
 }
}

void SaveImage::stampaCodice()
{
    QPrinter printer(QPrinter::HighResolution);

    QPrintPreviewDialog preview(&printer);
    preview.setWindowFlags(Qt::Window);
    preview.setWindowTitle(tr("Anteprima di stampa."));
    connect(&preview,SIGNAL(paintRequested(QPrinter*)),SLOT(anteprima(QPrinter*)));
    preview.exec();
}

void SaveImage::anteprima(QPrinter* printer)
{
    /*
     *FIXME Processo di stampa
    */
    Q_UNUSED(printer);

    printer->setPageSize(QPrinter::A7);
    QImage image_800x600 = QImage(":/images/codicefiscale_800x600.png");
    printer->setOrientation(QPrinter::Landscape);
    printer->setResolution(254);


     QPainter *painter = new QPainter(printer);

     painter->drawImage(5,5,image_800x600);
     painter->setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
     painter->drawText(60,190,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getCodice());
     painter->drawText(30,240,480,100, Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getSurname());
     painter->drawText(30,290,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap, getName());
     painter->drawText(40,340,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap, getComuneStato());
     painter->drawText(40,395,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getProvincia());
     painter->drawText(30,450,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getData());
     painter->drawText(480,335,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,getSesso());
     painter->setFont(QFont("Arial",12,50));
     painter->drawText(400,440,480,100,Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap,"FAC SIMILE");
     painter->end();
}

QString SaveImage::getSurname()
{
    return surname;
}

void SaveImage::setSurname(QString mSurname)
{
    surname = mSurname;
}

QString SaveImage::getName()
{
    return name;
}

void SaveImage::setName(QString names)
{
    name = names;
}

QString SaveImage::getSesso()
{
    return sesso;
}

void SaveImage::setSesso(QString m_sesso)
{
    sesso = m_sesso;
}

QString SaveImage::getComuneStato()
{
    return com;
}

void SaveImage::setComuneStato(QString comst)
{
    com = comst;
}

QString SaveImage::getProvincia()
{
    return prov;
}

void SaveImage::setProvincia(QString mProv)
{
    prov = mProv;
}

QString SaveImage::getCodice()
{
    return codiceFis;
}

void SaveImage::setCodice(QString mCodice)
{
    codiceFis = mCodice;
}

QString SaveImage::getData()
{
    return data;
}

void SaveImage::setData(QString mdata)
{
    data = mdata;
}

QString SaveImage::GetVersioneQt()
{
    return QT_VERSION_STR;
}
