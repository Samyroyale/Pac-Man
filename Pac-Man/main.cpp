int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.setStyleSheet("QMainWindow {background: 'black';}");
    window.show();

    MainWindow w;
    w.setStyleSheet("QMainWindow {background: 'black';}");
    w.show();
    return a.exec();
}
