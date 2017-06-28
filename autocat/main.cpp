//#include "mainwindow.h"
#include <QtWidgets>
//#include <QTextEdit>
//#include <QPushButton>
class Window : public QMainWindow{
    Q_OBJECT
public:
    Window(){

    }

private slots:
    void setBackground();
    void center();
private:

};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextEdit textEdit;
    QPushButton but("Hello");
    QVBoxLayout lay;
    lay.addWidget(&textEdit);
    lay.addWidget(&but);

    QWidget window;
    window.setLayout(&lay);
    window.show();
    return app.exec();
}
