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
#ifndef FIND_CAP_ITALIAN_H
#define FIND_CAP_ITALIAN_H

/*!
 * \author 2014 Codelinsoft <info@codelinsoft.it>
 */

#include <QDialog>

/*!
 * \brief namespace Ui{}
 * \param class find_cap_italian;
 */
namespace Ui {
class find_cap_italian;
}

/*!
 * La classe find_cap_italian è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QDialog.
 * \brief <b>class find_cap_italian: public QDdialog</b>
 * \param QDialog
 */
class find_cap_italian : public QDialog
{
    /*!
     * Macro Qt
     *
     *
     * \brief Q_OBJECT
     */
    Q_OBJECT
    
public:

    /*!
     * Costruttore <b>find_cap_italian(QWidget *parent = 0);</b>
     *
     * Questa classe visualizza le informazioni
     * relative alla verifica del CAP.
     *
     *
     * \brief <b>find_cap_italian(QWidget *parent = 0);</b>
     * \param parent = 0
     */
    explicit find_cap_italian(QWidget *parent = 0);

    //!Distruttore ~find_cap_italian();
     /*!
      * Il distruttore ~find_cap_italian(); serve a chiudere
      * gli eventuali processi attivi.
      *
      *\param delete ui;
      */
    ~find_cap_italian();
    
private:
    //! Variabile privata
    /*!
     * Variabile ui; Serve a visualizzare gli elementi
     * realizzati con il designer qt.
     *
     *
     * \brief <b>Ui::find_cap_italian *ui;<b/>
     * \param ui;
     */
    Ui::find_cap_italian *ui;

    /*!
     * Serve a visualizzare il CAP
     *
     * \brief <b>QString cap</b>
     */
    QString cap;

    /*!
     * Serve a trovare il CAP
     *
     * \brief <b>QString found</b>
     */
    QString found;
public slots:

    /*!
     * La funzione find_comune(); serve a trovare il codice
     * di appartenenza del comune selezionato.
     *
     *\brief <b>void find_comune();</b>
     */
    void find_comune();

    /*!
     * La funzione vis_cap_comune(); serve a estrarre 
     * il cap per il comune selezionato.
     *
     *\brief <b>void vis_cap_comune();</b>
     */
    void vis_cap_comune();

   /*!
     * La funzione cap_trovato(); visualizza 
     * il cap per il comune selezionato.
     *
     *\brief <b>void cap_trovato();</b>
     */
    void cap_trovato();

};

#endif // FIND_CAP_ITALIAN_H
