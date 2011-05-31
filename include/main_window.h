#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

#include "fichier_client.h"

class QAction;
class QMenu;
class QLabel;

class search_widget;

class main_window : public QMainWindow
 {
     Q_OBJECT

 public:
     main_window(void);

     void manage_features(bool p_enable);

 private slots:
     void test();
     void import();
     void open_db();
     void save();
     void save_as();
     void close_db();
     void exit();
 private:
     void closeEvent(QCloseEvent *event);
     void create_actions(void);
     void create_menus(void);
     void create_status_bar(void);

     QAction *m_import_file_action;
     QAction *m_open_file_action;
     QAction *m_save_action;
     QAction *m_save_as_action;
     QAction *m_close_action;
     QAction *m_exit_action;
     QAction *m_test_action;
     QMenu * m_file_menu;
     QLabel * m_status_label;
     search_widget * m_search_widget;
     fichier_client m_fichier_client;
 };

#endif
