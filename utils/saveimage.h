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

#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QtCore>
#include <QtWidgets>
#include <QtQml>
#include <QtQuick>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

class SaveImage : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString getName READ getName WRITE setName)
    Q_PROPERTY(QString getSurname READ getSurname WRITE setSurname)
    Q_PROPERTY(QString getSesso READ getSesso WRITE setSesso)
    Q_PROPERTY(QString getComuneStato READ getComuneStato WRITE setComuneStato)
    Q_PROPERTY(QString getProvincia READ getProvincia WRITE setProvincia)
    Q_PROPERTY(QString getCodice READ getCodice WRITE setCodice)
    Q_PROPERTY(QString getData READ getData WRITE setData)
    
public:
    explicit SaveImage(QQuickItem *parent = 0);
    
    Q_INVOKABLE void saveImages(QQuickItem *item);
    Q_INVOKABLE void exportPdf();
    Q_INVOKABLE void stampaCodice();
    Q_INVOKABLE QString GetVersioneQt();
    
    //Cognome
    QString surname;
    QString getSurname();
    void setSurname(QString mSurname);
    //Nome
    QString name;
    QString getName();
    void setName(QString names);
    //Sesso
    QString sesso;
    QString getSesso();
    void setSesso(QString m_sesso);
    //Comune o stato
    QString com;
    QString getComuneStato();
    void setComuneStato(QString comst);
    //Provincia
    QString prov;
    QString getProvincia();
    void setProvincia(QString mProv);
    //CodiceFiscale
    QString codiceFis;
    QString getCodice();
    void setCodice(QString mCodice);
    //Data di nascita
    QString data;
    QString getData();
    void setData(QString mdata);
        
public slots:
    void anteprima(QPrinter *printer);
    
private:
    QPainter *painter;
};

#endif // SAVEIMAGE_H
