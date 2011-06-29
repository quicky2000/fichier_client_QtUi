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
     //---------------------------------------------------
     // Methods inherited from fichier_client_UI_if class
     //---------------------------------------------------
     void display_warning_message(const std::string & p_title,const std::string & p_text);
     void display_information_message(const std::string & p_title,const std::string & p_text);

     void set_facture_creation_for_selected_livre_enabled( bool p_enabled);
     void set_delete_livre_facture_enabled(bool p_enabled);
     void set_modify_livre_facture_enabled(bool p_enabled);
     void refresh_list_facture_of_livre_facture(void);
     void set_non_attributed_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs);
     void set_non_attributed_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids);
     void set_non_attributed_facture_status_list(const std::vector<facture_status> & p_status_list);
     const std::string get_non_attributed_facture_date(void)const;
     uint32_t get_non_attributed_facture_livre_facture_id(void)const;
     uint32_t get_non_attributed_facture_reference(void)const;
     const facture_status * get_non_attributed_facture_status(void)const;
     void clear_non_attributed_facture_date(void);
     void enable_non_attributed_facture_fields(bool p_enable);
     bool is_non_attributed_facture_date_complete(void);
     bool is_non_attributed_facture_date_empty(void);
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
