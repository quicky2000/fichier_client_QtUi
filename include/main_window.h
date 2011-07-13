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
class customer_data_widget;
class livre_facture_widget;
class facture_status_widget;
class facture_reason_widget;

class main_window : public QMainWindow, public fichier_client_UI_if
{
  Q_OBJECT

    public:
  main_window(void);

  void manage_features(bool p_enable);
  //---------------------------------------------------
  // Methods inherited from fichier_client_UI_if class
  //---------------------------------------------------
  // Comunication with user
  void display_warning_message(const std::string & p_title,const std::string & p_text);
  void display_information_message(const std::string & p_title,const std::string & p_text);

  // Interactions with customer search information
  const std::string get_search_customer_name(void)const;
  const std::string get_search_customer_first_name(void)const;
  const std::string get_search_customer_address(void)const;
  const std::string get_search_customer_city(void)const;
  uint32_t get_selected_customer(void)const;
  void update_search_customer_list(const std::vector<search_client_item> & p_list);
  void update_search_customer_list_achat(const std::vector<search_achat_item> & p_list);
  void update_search_customer_list_facture(const std::vector<search_facture_item> & p_list);

  void set_customer_search_add_customer_enabled(bool p_enabled);
  void set_customer_search_modify_customer_enabled(bool p_enabled);
  void set_customer_search_delete_customer_enabled(bool p_enabled);

  // Interactions with Customer identity information
  void set_customer_name(const std::string & p_name);
  const std::string get_customer_name(void)const;
  void set_customer_first_name(const std::string & p_first_name);
  const std::string get_customer_first_name(void)const;
  void set_customer_phone(const std::string & p_phone);
  const std::string get_customer_phone(void)const;
  void set_customer_address(const std::string & p_address);
  const std::string get_customer_address(void)const;

  // Interactions with livre facture information
  void clear_livre_facture_information(void);
  void set_livre_facture_start_date(const std::string & p_date);
  void set_livre_facture_end_date(const std::string & p_date);
  void set_livre_facture_id(const std::string & p_id);
  const std::string get_livre_facture_start_date(void)const;
  bool is_livre_facture_start_date_complete(void)const;
  const std::string get_livre_facture_end_date(void)const;
  bool is_livre_facture_end_date_complete(void)const;
  const std::string get_livre_facture_id(void)const;

  // Interactions with livre facture list
  bool is_livre_facture_selection_empty(void)const;
  uint32_t get_selected_livre_facture_id(void)const;
  void refresh_livre_facture_list(std::vector<livre_facture> & p_list);

  // Interactions with livre facture actions
  void set_delete_livre_facture_enabled(bool p_enabled);
  void set_modify_livre_facture_enabled(bool p_enabled);
  void set_create_livre_facture_enabled(bool p_enabled);

  // Interactions with non attribtued facture information
  void set_non_attributed_facture_date(const std::string & p_date);
  void set_non_attributed_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs);
  void set_non_attributed_facture_reference(uint32_t p_ref);
  void set_non_attributed_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids);
  void set_non_attributed_facture_status_list(const std::vector<facture_status> & p_status_list);
  void set_non_attributed_facture_status(uint32_t p_id);
  void set_non_attributed_facture_reason_list(const std::vector<facture_reason> & p_reason_list);
  void set_non_attributed_facture_reason(uint32_t p_id);
  const std::string get_non_attributed_facture_date(void)const;
  uint32_t get_non_attributed_facture_livre_facture_id(void)const;
  uint32_t get_non_attributed_facture_reference(void)const;
  const facture_status * get_non_attributed_facture_status(void)const;
  const facture_reason * get_non_attributed_facture_reason(void)const;
  void clear_non_attributed_facture_date(void);
  void enable_non_attributed_facture_fields(bool p_enable);
  bool is_non_attributed_facture_date_complete(void)const;
  bool is_non_attributed_facture_date_empty(void)const;
  
  // Interactions with non attributed facture list
  void refresh_list_facture_of_livre_facture(std::vector<search_facture_client_item> & p_list);
  bool is_list_facture_of_livre_facture_selection_empty(void)const;
  uint32_t get_list_facture_of_livre_facture_selected_id(void)const;

  // Interactions with non attributed facture buttons
  void set_facture_creation_for_selected_livre_enabled( bool p_enabled);
  void set_facture_deletion_for_selected_livre_enabled( bool p_enabled);
  void set_facture_modification_for_selected_livre_enabled( bool p_enabled);

  // Interactions with facture status information
  void clear_facture_status_information(void);
  void set_facture_status_name(const std::string & p_name);  
  const std::string get_facture_status_name(void)const;

  // Interactions with facture status list
  bool is_facture_status_selection_empty(void)const;
  uint32_t get_selected_facture_status_id(void)const;
  void refresh_facture_status_list(std::vector<facture_status> & p_list);
  void set_facture_status_list_enabled(bool p_enable);

  // Interactions with facture status actions
  void set_create_facture_status_enabled(bool p_enable);
  void set_delete_facture_status_enabled(bool p_enable);
  void set_modify_facture_status_enabled(bool p_enable);
  void set_modify_facture_status_action_name(const std::string & p_name);

  // Interactions with facture reason information
  void clear_facture_reason_information(void);
  void set_facture_reason_name(const std::string & p_name);  
  const std::string get_facture_reason_name(void)const;

  // Interactions with facture reason list
  bool is_facture_reason_selection_empty(void)const;
  uint32_t get_selected_facture_reason_id(void)const;
  void refresh_facture_reason_list(std::vector<facture_reason> & p_list);
  void set_facture_reason_list_enabled(bool p_enable);

  // Interactions with facture reason actions
  void set_create_facture_reason_enabled(bool p_enable);
  void set_delete_facture_reason_enabled(bool p_enable);
  void set_modify_facture_reason_enabled(bool p_enable);
  void set_modify_facture_reason_action_name(const std::string & p_name);

  private slots:
  void treat_test_event();
  void treat_import_event();
  void treat_open_db_event();
  void treat_save_event();
  void treat_save_as_event();
  void treat_close_db_event();
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
  customer_data_widget * m_customer_data_widget;
  livre_facture_widget *m_livre_facture_widget;
  facture_status_widget *m_facture_status_widget;
  facture_reason_widget *m_facture_reason_widget;
  fichier_client m_fichier_client;
};

#endif
