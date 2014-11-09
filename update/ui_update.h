/********************************************************************************
** Form generated from reading UI file 'update.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATE_H
#define UI_UPDATE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_update
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QProgressBar *unzip_file;
    QPushButton *dw_ps;
    QProgressBar *progressBar;
    QLabel *textEdit;
    QLabel *label_2;
    QLabel *test_agg;
    QLabel *label_3;
    QLabel *label;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *inst_agg;
    QPushButton *down_agg;

    void setupUi(QDialog *update)
    {
        if (update->objectName().isEmpty())
            update->setObjectName(QString::fromUtf8("update"));
        update->resize(524, 321);
        gridLayout_3 = new QGridLayout(update);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(update);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        unzip_file = new QProgressBar(groupBox);
        unzip_file->setObjectName(QString::fromUtf8("unzip_file"));
        unzip_file->setValue(0);

        gridLayout->addWidget(unzip_file, 4, 1, 1, 1);

        dw_ps = new QPushButton(groupBox);
        dw_ps->setObjectName(QString::fromUtf8("dw_ps"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        dw_ps->setIcon(icon);

        gridLayout->addWidget(dw_ps, 4, 2, 1, 1);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 4, 0, 1, 1);

        textEdit = new QLabel(groupBox);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 6, 0, 1, 3);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/codice_fiscale_logo.png")));

        gridLayout->addWidget(label_2, 0, 0, 1, 3);

        test_agg = new QLabel(groupBox);
        test_agg->setObjectName(QString::fromUtf8("test_agg"));

        gridLayout->addWidget(test_agg, 5, 0, 1, 3);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(update);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 0, 1, 1);

        inst_agg = new QPushButton(groupBox_2);
        inst_agg->setObjectName(QString::fromUtf8("inst_agg"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/install.png"), QSize(), QIcon::Normal, QIcon::Off);
        inst_agg->setIcon(icon1);

        gridLayout_2->addWidget(inst_agg, 0, 1, 1, 1);

        down_agg = new QPushButton(groupBox_2);
        down_agg->setObjectName(QString::fromUtf8("down_agg"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/upgrade.png"), QSize(), QIcon::Normal, QIcon::Off);
        down_agg->setIcon(icon2);

        gridLayout_2->addWidget(down_agg, 0, 2, 1, 1);

        down_agg->raise();
        inst_agg->raise();

        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(update);

        QMetaObject::connectSlotsByName(update);
    } // setupUi

    void retranslateUi(QDialog *update)
    {
        update->setWindowTitle(QApplication::translate("update", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        unzip_file->setFormat(QString());
#ifndef QT_NO_TOOLTIP
        dw_ps->setToolTip(QApplication::translate("update", "<html><head/><body><p>Annulla download</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dw_ps->setText(QString());
        progressBar->setFormat(QString());
        textEdit->setText(QString());
        label_2->setText(QString());
        test_agg->setText(QString());
        label_3->setText(QApplication::translate("update", "Installazione", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("update", "<html><head/><body><p>Download aggiornamento</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        inst_agg->setToolTip(QApplication::translate("update", "<html><head/><body><p>Installa aggiornamento</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        inst_agg->setText(QApplication::translate("update", "Installa aggiornamento", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        down_agg->setToolTip(QApplication::translate("update", "<html><head/><body><p>Download aggiornamento</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        down_agg->setText(QApplication::translate("update", "Downaload aggiornamento", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class update: public Ui_update {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATE_H
