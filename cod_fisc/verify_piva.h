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
#ifndef VERIFY_PIVA_H
#define VERIFY_PIVA_H

/*!
 * \author 2014 Codelinsoft <info@codelinsoft.it>
 */

#include <QDialog>

/*!
 * \brief namespace Ui{}
 * \param class verify_piva;
 */
namespace Ui {
class verify_piva;
}

/*!
 * La classe verify_codicefiscale è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QDialog.
 * \brief <b>class verify_piva: public QDdialog</b>
 * \param QDialog
 */
class verify_piva : public QDialog
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
     * Costruttore <b>verify_piva(QWidget *parent = 0);</b>
     *
     * Questa classe visualizza le informazioni
     * relative alla verifica della partita iva.
     *
     *
     * \brief <b>verify_piva(QWidget *parent = 0);</b>
     * \param parent = 0
     */
    explicit verify_piva(QWidget *parent = 0);

    //!Distruttore ~verify_piva();
     /*!
      * Il distruttore ~verify_piva(); serve a chiudere
      * gli eventuali processi attivi.
      *
      *\param delete ui;
      */
    ~verify_piva();
    
public slots:

    /*!
     * La funzione verify() serve a lanciare il
     * comando di verifica della partita iva.
     *
     *\brief <b>verify();</b>
     */
    void verify();

    /*!
     * La funzione read_codice_fis(QString code)
     * serve a leggere e verificare la partita
     * iva.
     *
     *\brief <b>read_codice_fis(QString code);</b>
     *\param QString code;----------------[<b>Il parametro code serve a leggere la partita iva e verificarla.</b>]
     */
    QString read_piva(QString code);
private:
    //! Variabile privata
    /*!
     * Variabile ui; Serve a visualizzare gli elementi
     * realizzati con il designer qt.
     *
     *
     * \brief <b>Ui::verify_piva *ui;<b/>
     * \param ui;
     */
    Ui::verify_piva *ui;
};

#endif // VERIFY_PIVA_H
