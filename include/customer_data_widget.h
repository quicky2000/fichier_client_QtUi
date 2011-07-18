#ifndef _CUSTOMER_DATA_WIDGET_H_
#define _CUSTOMER_DATA_WIDGET_H_

#include <QWidget>
#include "ville.h"
#include "search_facture_item.h"
#include "search_achat_item.h"
#include "facture_status.h"
class fichier_client;

class QLineEdit;
class QPushButton;
class QComboBox;
class QCheckBox;
class base_facture_widget;
class facture_list_table;
class achat_list_table;

class customer_data_widget: public QWidget
{
  Q_OBJECT
    public:
  customer_data_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);

  // Interactions with customer identity information
  void set_name(const std::string & p_name);
  const std::string get_name(void)const;
  void set_first_name(const std::string & p_first_name);
  const std::string get_first_name(void)const;
  void set_phone(const std::string & p_phone);
  const std::string get_phone(void)const;
  bool is_phone_empty(void)const;
  bool is_phone_complete(void)const;
  void set_address(const std::string & p_address);
  const std::string get_address(void)const;
  void set_postal_code(const std::string & p_postal_code);
  const std::string get_postal_code(void)const;
  void set_city_list(const std::vector<ville> & p_list);
  const ville * get_city(void)const;
  void set_identity_fields_enabled(bool p_enabled);

  // Interactions with customer identity actions
  void set_create_customer_enabled(bool p_enabled);
  void set_modify_customer_enabled(bool p_enabled);
  void set_delete_customer_enabled(bool p_enabled);

  // Interactions with customer bill information
  void set_bill_fields_enabled(bool p_enabled);
  void set_facture_date(const std::string & p_date);
  void set_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids);
  void set_facture_livre_id(uint32_t p_id);
  void set_facture_allowed_references(const std::vector<uint32_t> & p_remaining_refs);
  void set_facture_reference(uint32_t p_ref);
  void set_facture_status_list(const std::vector<facture_status> & p_status_list);
  void set_facture_status(uint32_t p_id);
  bool is_bill_date_complete(void)const;
  bool is_bill_date_empty(void)const;
  const std::string get_bill_date(void)const;
  uint32_t get_bill_book_id(void)const;
  uint32_t get_bill_reference(void)const;
  const facture_status * get_bill_status(void)const;

  // Interactions with customer bill list
  bool is_bill_selection_empty(void)const;
  uint32_t get_selected_bill_id(void)const;
  void update_bill_list(const std::vector<search_facture_item> & p_list);
  void set_bill_list_enabled(bool p_enabled);

  // Interactions with customer bill actions
  void set_bill_creation_enabled(bool p_enabled);
  void set_bill_modification_enabled(bool p_enabled);
  void set_bill_deletion_enabled(bool p_enabled);
   
  // Interactions with customer purchase information
  void set_purchase_fields_enabled(bool p_enabled);

  // Interactions with customer purchase list  
  void update_purchase_list(const std::vector<search_achat_item> & p_list);
  void set_purchase_list_enabled(bool p_enabled);

  // Interactions with customer purchase actions
  void set_purchase_creation_enabled(bool p_enabled);
  void set_purchase_modification_enabled(bool p_enabled);
  void set_purchase_deletion_enabled(bool p_enabled);

  private slots:
  // Customer identity information event handlers
  void treat_postal_code_modification_event(void);
  void treat_city_selection_event(void);
  void treat_identity_content_modification_event(void);

  // Customer identity actions event handlers
  void treat_create_customer_event(void);
  void treat_modify_customer_event(void);
  void treat_delete_customer_event(void);

  // Customer bill information event handlers
  void treat_date_modification_event(void);
  void treat_bill_ref_selected_event(void);
  void treat_bill_book_selected_event(void);
  void treat_status_selected_event(void);

  // Customer bill list event handlers
  void treat_bill_selected_event(void);
  void treat_bill_selection_changed_event(void);

  // Customer bill action event handlers
  void treat_create_bill_event(void);
  void treat_modify_bill_event(void);
  void treat_delete_bill_event(void);
   
 private:
  // Customer identity information
  QLineEdit * m_name_field;
  QLineEdit * m_first_name_field;
  QLineEdit * m_phone_field;
  QLineEdit * m_address_field;
  QLineEdit * m_postal_code_field;
  QComboBox * m_city_field;
  // Customer identity actions
  QPushButton * m_create_customer_button;
  QPushButton * m_modify_customer_button;
  QPushButton * m_delete_customer_button;
  // Customer bill information
  base_facture_widget * m_bill_widget;
  // Customer bill list
  facture_list_table *m_bill_list_table;
  // Customer bill actions
  QPushButton * m_create_bill_button;
  QPushButton * m_modify_bill_button;
  QPushButton * m_delete_bill_button;
  // Customer purchase information
  QComboBox * m_brand_field;
  QComboBox * m_type_field;
  QLineEdit * m_purchase_reference_field;
  QLineEdit * m_euro_price_field;
  QLineEdit * m_franc_price_field;
  QCheckBox * m_warranty_field;
  // Customer purchase list
  achat_list_table *m_purchase_list_table;
  // Customer purchase actions
  QPushButton * m_create_purchase_button;
  QPushButton * m_modify_purchase_button;
  QPushButton * m_delete_purchase_button;


  std::vector<ville> m_cities;
  fichier_client & m_fichier_client;
};
#endif
