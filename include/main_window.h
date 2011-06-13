#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

#include "fichier_client.h"
#include "fichier_client_UI_if.h"

class QAction;
class QMenu;
class QLabel;
class QTabWidget;

class search_widget;
class livre_facture_widget;
class facture_status_widget;

class main_window : public QMainWindow, public fichier_client_UI_if
 {
     Q_OBJECT

 public:
     main_window(void);

     void manage_features(bool p_enable);
     // Methods inherited from fichier_client_UI_if class
     void display_warning_message(const std::string & p_title,const std::string & p_text);
     void display_information_message(const std::string & p_title,const std::string & p_text);
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
     QTabWidget *m_tab_widget;
     search_widget * m_search_widget;
     livre_facture_widget *m_livre_facture_widget;
     facture_status_widget *m_facture_status_widget;
     fichier_client m_fichier_client;
 };

#endif
