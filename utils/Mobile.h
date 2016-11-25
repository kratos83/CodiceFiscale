#ifndef MOBILE_H
#define MOBILE_H

#include <QObject>
#include <QScreen>
#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#endif


class Mobile: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isMobile READ isMobile NOTIFY isMobileChanged)
    Q_PROPERTY(qreal dpi READ Dpi NOTIFY dpiChanged)

public:
    explicit Mobile(QObject *parent = 0);
    ~Mobile();

    Q_INVOKABLE qreal dpi( int value ) { return m_dpi*value; }

    bool isMobile() const { return m_isMobile; }
    qreal Dpi() const { return m_dpi; }

signals:

    void isMobileChanged(bool arg);
    void dpiChanged(qreal arg);

public slots:

private:
    bool m_isMobile;
    QScreen *m_screen;
    int m_dpi;
    qreal mDpi;
};

#endif //MOBILE_H
