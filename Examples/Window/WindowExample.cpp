#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QWidget      window;
    window.setWindowTitle("Qt Sample");
    window.resize(300, 200);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QTabWidget*  tabWidget  = new QTabWidget;

    // First tab
    QWidget*     tab1       = new QWidget;
    QVBoxLayout* tab1Layout = new QVBoxLayout;

    QLabel*      nameLabel  = new QLabel("Name:");
    QLineEdit*   nameInput  = new QLineEdit;
    QHBoxLayout* nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameInput);
    tab1Layout->addLayout(nameLayout);

    tab1->setLayout(tab1Layout);
    tabWidget->addTab(tab1, "Tab 1");

    // Second tab
    QWidget*     tab2       = new QWidget;
    QVBoxLayout* tab2Layout = new QVBoxLayout;

    QPushButton* button = new QPushButton("Click me");
    tab2Layout->addWidget(button);

    tab2->setLayout(tab2Layout);
    tabWidget->addTab(tab2, "Tab 2");

    mainLayout->addWidget(tabWidget);
    window.setLayout(mainLayout);
    window.show();

    return app.exec();
}
