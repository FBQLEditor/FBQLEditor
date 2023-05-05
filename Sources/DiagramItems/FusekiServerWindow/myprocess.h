#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QProcess>
#include <QThread>

class MyProcess : public QThread
{
    Q_OBJECT
public:
    explicit MyProcess( QObject* parent = nullptr );
    ~MyProcess();

public slots:
    void run() override;
    void runCommand( QString );
    void stopCommand();

private:
    QProcess process;
};

#endif // MYPROCESS_H
