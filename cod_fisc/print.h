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
#ifndef PRINT_H
#define PRINT_H

/*!
 * \author 2014 Codelinsoft <info@codelinsoft.it>
 */

#include <QPrinter>
#include <QPainter>
#include <QDialog>
#include <QPrintDialog>
#include <QtGui>
#include <QAbstractPrintDialog>

/*!
 * La classe print è una classe
 * che eredita le funzioni dalla classe
 * QPrinter.
 * \brief <b>class print<b>
 */
class print
{
public:
    /*!
     * Costruttore <b>print();</b>
     *
     * Questa classe visualizza la una finestra di dialogo
     * per la stampa dei documenti.
     *
     * \brief <b>print();</b>
     */
    print();

    /*!
     * La funzione print_codice(QPrinter *printer, QImage img, QString cognome, QString nome, bool maschio, bool femmina,
     *                          QString com_st, QString pr_st, QString codice, QDate date)
     * visualizza la stampa del codice fiscale.
     *
     *\brief <b>print_codice(QPrinter *printer, QImage img, QString cognome, QString nome, bool maschio, bool femmina,
     *                          QString com_st, QString pr_st, QString codice, QDate date)</b>
     *\param QPrinter *printer;------------[<b>Il paramatro painter serve a poter visualizzare la stampa grazie alla classe QPrinter,QPainter</b>]
     *\param QImage img;-------------------[<b>Il parametro img serve a visualizzare l'immagine da stampare</b>]
     *\param QString cognome;--------------[<b>Il parametro cognome serve a visualizzare il cognome dell'utente desiderato.</b>]
     *\param QString nome;-----------------[<b>Il parametro nome serve a visualizzare il nome dell'utente desiderato.</b>]
     *\param bool maschio;-----------------[<b>Il parametro maschio ritorna vero se è esatto.</b>]
     *\param bool femmina;-----------------[<b>Il parametro femmina ritorna vero se è esatto.</b>]
     *\param QString com_st;---------------[<b>Il parametro com_st serve a visualizzare il comune o lo stato di nascita.</b>]
     *\param QString pr_st;----------------[<b>Il parametro pr_st serve a visualizzare la provincia di nascita.</b>]
     *\param QString codice;---------------[<b>Il parametro codice serve a visualizzare il codice fiscale completo.</b>]
     *\param QDate date;-------------------[<b>Il parametro date serve a visualizzare la data di nascita.</b>]
     */
    void print_codice(QPrinter *printer, QImage img, QString cognome, QString nome, bool maschio, bool femmina,
                      QString com_st, QString pr_st, QString codice, QDate date);

    /*!
     * Il paramatro printer serve a poter visualizzare
     * la stampa grazie alla classe QPrinter,QPainter.
     *
     * \brief <b>QPrinter *printer</b>
     */
    QPrinter *printer;

    /*!
     * Il paramatro painter serve a poter visualizzare
     * la stampa grazie alla classe QPrinter,QPainter.
     *
     * \brief <b>QPainter *painter</b>
     */
    QPainter *painter;

    /*!
     * Il puntatore *stampaDlg serve a visualizzare
     * una finestra di dialogo con le caratteristiche
     * della stampa.
     * \brief <b>QDialog *stampaDlg</b>
     */
    QPrintDialog *stampaDlg;
};

#endif // PRINT_H
