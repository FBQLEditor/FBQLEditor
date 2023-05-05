#include "myprocess.h"

MyProcess::MyProcess( QObject* parent )
    : QThread( parent )
{
}

MyProcess::~MyProcess()
{
    process.terminate();
}

void MyProcess::run()
{
}

void MyProcess::runCommand( QString cmd )
{
    process.start( cmd );
}

void MyProcess::stopCommand()
{
    process.terminate();
}
