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
class purchase_configuration_widget;
class city_widget;
class coherency_report_widget;

class main_window : public QMainWindow, public fichier_client_UI_if
{
  Q_OBJECT

    public:
  main_window(void);

  //---------------------------------------------------
  // Methods inherited from fichier_client_UI_if class
  //---------------------------------------------------
  // Comunication with user
  void display_warning_message(const std::string & p_title,const std::string & p_text);
  void display_information_message(const std::string & p_title,const std::string & p_text);
  void display_status_message(const std::string & p_text);
  const std::string get_readable_date(const std::string & p_date)const;
  void set_application_title(const std::string & p_name);
  bool ask_yes_no_qestion(const std::string & p_title, const std::string & p_question);

  // Interactions with main actions
  void set_import_file_action_enabled(bool p_enabled);
  void set_open_file_action_enabled(bool p_enabled);
  void set_save_file_action_enabled(bool p_enabled);
  void set_save_as_file_action_enabled(bool p_enabled);
  void set_close_file_action_enabled(bool p_enabled);
  void set_exit_file_action_enabled(bool p_enabled);

  // Interactions with customer search information
  void set_customer_search_enabled(bool p_enabled);
  void set_focus_on_customer_search(void);
  void clear_customer_search_criteria(void);
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
  void set_focus_on_customer_data(void);
  void set_customer_name(const std::string & p_name);
  const std::string get_customer_name(void)const;
  void set_customer_first_name(const std::string & p_first_name);
  const std::string get_customer_first_name(void)const;
  void set_customer_phone(const std::string & p_phone);
  const std::string get_customer_phone(void)const;
  bool is_customer_phone_empty(void)const;
  bool is_customer_phone_complete(void)const;
  void set_customer_address(const std::string & p_address);
  const std::string get_customer_address(void)const;
  void set_customer_postal_code(const std::string & p_postal_code);
  const std::string get_customer_postal_code(void)const;
  void set_customer_city_list(const std::vector<ville> & p_list);
  const ville * get_customer_city(void)const;
  void set_customer_data_identity_fields_enabled(bool p_enabled);
  void set_customer_data_create_customer_enabled(bool p_enabled);
  void set_customer_data_modify_customer_enabled(bool p_enabled);
  void set_customer_data_delete_customer_enabled(bool p_enabled);

  // Interactions with customer bill information
  void set_customer_bill_fields_enabled(bool p_enabled);
  void set_customer_facture_date(const std::string & p_date);
  void set_customer_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids);
  void set_customer_facture_livre_id(uint32_t p_id);
  void set_customer_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs);
  void set_customer_facture_reference(uint32_t p_ref);
  void set_customer_facture_status_list(const std::vector<facture_status> & p_status_list);
  void set_customer_facture_status(uint32_t p_id);
  bool is_customer_bill_date_complete(void)const;
  bool is_customer_bill_date_empty(void)const;
  const std::string get_customer_bill_date(void)const;
  uint32_t get_customer_bill_book_id(void)const;
  uint32_t get_customer_bill_reference(void)const;
  const facture_status * get_customer_bill_status(void)const;

  // Interactions with customer bill list
  bool is_customer_data_bill_selection_empty(void)const;
  uint32_t get_customer_data_selected_bill_id(void)const;
  void update_customer_data_bill_list(const std::vector<search_facture_item> & p_list);
  void set_customer_bill_list_enabled(bool p_enabled);

  // Interactions with customer bill actions
  void set_customer_bill_creation_enabled(bool p_enabled);
  void set_customer_bill_modification_enabled(bool p_enabled);
  void set_customer_bill_deletion_enabled(bool p_enabled);

  // Interactions with customer purchase information
  void set_customer_purchase_fields_enabled(bool p_enabled);
  void set_customer_purchase_brand_list(const std::vector<marque> & p_list);
  void set_customer_purchase_brand(uint32_t p_id);
  void set_customer_purchase_type_list(const std::vector<type_achat> & p_list);
  void set_customer_purchase_type(uint32_t p_id);
  void set_customer_purchase_reference(const std::string & p_ref);
  void set_customer_purchase_euro_price(const std::string & p_euro_price);
  void set_customer_purchase_franc_price(const std::string & p_franc_price);
  void set_customer_purchase_warranty(bool p_warranty);
  const marque * get_customer_purchase_brand(void)const;
  const type_achat * get_customer_purchase_type(void)const;
  const std::string get_customer_purchase_reference(void)const; 
  const std::string get_customer_purchase_euro_price(void)const; 
  const std::string get_customer_purchase_franc_price(void)const; 
  bool is_customer_purchase_warranty_selected(void)const;

  // Interactions with customer purchase list
  bool is_customer_data_purchase_selection_empty(void)const;
  uint32_t get_customer_data_selected_purchase_id(void)const;  
  void update_customer_data_purchase_list(const std::vector<search_achat_item> & p_list);
  void set_customer_purchase_list_enabled(bool p_enabled);

  // Interactions with customer purchase actions
  void set_customer_purchase_creation_enabled(bool p_enabled);
  void set_customer_purchase_modification_enabled(bool p_enabled);
  void set_customer_purchase_deletion_enabled(bool p_enabled);

  // Interactions with livre facture information
  void set_livre_facture_information_enabled(bool p_enabled);
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

  // Interactions with non attributed facture information
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
  void set_facture_status_information_enabled(bool p_enabled);
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
  void set_facture_reason_information_enabled(bool p_enabled);
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

  // Interactions with brand information
  void set_purchase_configuration_enabled(bool p_enabled);
  void clear_purchase_configuration_brand_information(void);
  void set_purchase_configuration_brand_name(const std::string & p_name);  
  const std::string get_purchase_configuration_brand_name(void)const;

  // Interactions with brand list
  bool is_purchase_configuration_brand_selection_empty(void)const;
  uint32_t get_purchase_configuration_selected_brand_id(void)const;
  void set_purchase_configuration_brand_list(std::vector<marque> & p_list);
  void set_purchase_configuration_brand_list_enabled(bool p_enable);

  // Interactions with brand actions
  void set_purchase_configuration_create_brand_enabled(bool p_enable);
  void set_purchase_configuration_delete_brand_enabled(bool p_enable);
  void set_purchase_configuration_modify_brand_enabled(bool p_enable);
  void set_purchase_configuration_modify_brand_action_name(const std::string & p_name);

  // Interactions with type information
  void clear_purchase_configuration_type_information(void);
  void set_purchase_configuration_type_name(const std::string & p_name);  
  const std::string get_purchase_configuration_type_name(void)const;

  // Interactions with type list
  bool is_purchase_configuration_type_selection_empty(void)const;
  uint32_t get_purchase_configuration_selected_type_id(void)const;
  void set_purchase_configuration_type_list(std::vector<type_achat> & p_list);
  void set_purchase_configuration_type_list_enabled(bool p_enable);

  // Interactions with type actions
  void set_purchase_configuration_create_type_enabled(bool p_enable);
  void set_purchase_configuration_delete_type_enabled(bool p_enable);
  void set_purchase_configuration_modify_type_enabled(bool p_enable);
  void set_purchase_configuration_modify_type_action_name(const std::string & p_name);

  // Interactions with city information
  void set_city_information_enabled(bool p_enabled);
  void clear_city_information(void);
  void set_city_name(const std::string & p_name);  
  const std::string get_city_name(void)const;
  void set_city_postal_code(const std::string & p_postal_code);  
  const std::string get_city_postal_code(void)const;
  bool is_city_postal_code_complete(void)const;

  // Interactions with city list
  bool is_city_selection_empty(void)const;
  uint32_t get_selected_city_id(void)const;
  void set_city_list(std::vector<ville> & p_list);
  void set_city_list_enabled(bool p_enable);

  // Interactions with city actions
  void set_create_city_enabled(bool p_enable);
  void set_delete_city_enabled(bool p_enable);
  void set_modify_city_enabled(bool p_enable);
  void set_modify_city_action_name(const std::string & p_name);

  // Interactions with coherency actions
  void set_coherency_information_enabled(bool p_enabled);
  void set_coherency_report_launch_check_enabled(bool p_enable);

  // Interactions with coherency information
  void set_coherency_report_error_number(uint32_t p_nb);
  void set_coherency_report_error_list(std::vector<coherency_report_item> p_list);
  void set_coherency_report_warning_number(uint32_t p_nb);
  void set_coherency_report_warning_list(std::vector<coherency_report_item> p_list);

  private slots:
  void treat_tab_changed_event(int index);
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
  purchase_configuration_widget * m_purchase_configuration_widget;
  city_widget * m_city_widget;
  coherency_report_widget * m_coherency_report_widget;
  fichier_client m_fichier_client;
  bool m_in_customer_data_widget;
};

#endif
