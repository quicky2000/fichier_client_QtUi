#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QFileDialog>
#include <QFrame>
#include <QLineEdit>
#include <QHBoxLayout>

#include "fichier_client.h"
#include "client_list_table.h"
#include "achat_list_table.h"

class main_window : public QMainWindow
 {
     Q_OBJECT

 public:
     main_window(void);

 private slots:
     void open();
     void exit();
     void criteria_modification();
     void client_selected(int row);
 private:
     void closeEvent(QCloseEvent *event);
     void create_actions(void);
     void create_menus(void);
     void create_status_bar(void);

     QAction *m_open_file_action;
     QAction *m_exit_action;
     QMenu * m_file_menu;
     QLabel * m_status_label;
     QLineEdit * m_name_field;
     QLineEdit * m_first_name_field;
     QLineEdit * m_city_field;
     client_list_table *m_client_list_table;
     achat_list_table *m_achat_list_table;
     fichier_client m_fichier_client;
 };

#endif
