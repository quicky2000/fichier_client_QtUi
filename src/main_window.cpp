#include "main_window.h"
#include "test.h"
#include "my_date_widget.h"
#include "search_widget.h"
#include "customer_data_widget.h"
#include "livre_facture_widget.h"
#include "facture_status_widget.h"
#include "facture_reason_widget.h"
#include "purchase_configuration_widget.h"
#include "city_widget.h"

#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QMessageBox>
#include <QStatusBar>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMenuBar>
#include <QDialog>

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
main_window::main_window(void):
  m_import_file_action(NULL),
  m_open_file_action(NULL),
  m_save_action(NULL),
  m_save_as_action(NULL),
  m_close_action(NULL),
  m_exit_action(NULL),
  m_test_action(NULL),
  m_file_menu(NULL),
  m_status_label(NULL),
  m_search_widget(NULL),
  m_customer_data_widget(NULL),
  m_livre_facture_widget(NULL),
  m_facture_status_widget(NULL),
  m_facture_reason_widget(NULL),
  m_purchase_configuration_widget(NULL),
  m_city_widget(NULL)
{
  setWindowTitle(tr("Fichier client"));
  create_actions();
  create_menus();
  create_status_bar();

  m_tab_widget = new QTabWidget();

  m_livre_facture_widget = new livre_facture_widget(m_fichier_client);

  // Search widget
  m_search_widget = new search_widget(m_fichier_client);

  m_customer_data_widget = new customer_data_widget(m_fichier_client);

  m_facture_status_widget = new facture_status_widget(m_fichier_client);

  m_facture_reason_widget = new facture_reason_widget(m_fichier_client);

  m_purchase_configuration_widget = new purchase_configuration_widget(m_fichier_client);

  m_city_widget = new city_widget(m_fichier_client);

  m_tab_widget->addTab(m_search_widget,tr("Search"));
  m_tab_widget->addTab(m_customer_data_widget,tr("Donnees Client"));
  m_tab_widget->addTab(m_livre_facture_widget,tr("Livre facture"));
  m_tab_widget->addTab(m_facture_status_widget,tr("Facture status"));
  m_tab_widget->addTab(m_facture_reason_widget,tr("Facture reason"));
  m_tab_widget->addTab(m_purchase_configuration_widget,tr("Achat configuration"));
  m_tab_widget->addTab(m_city_widget,tr("Ville configuration"));

  setCentralWidget(m_tab_widget);

  manage_features(false);

  setMinimumSize(160, 160);
  resize(1024, 768);

  m_fichier_client.set_user_interface(this);
}

//------------------------------------------------------------------------------
void main_window::manage_features(bool p_enable)
{
  m_search_widget->set_enable(p_enable);
  m_livre_facture_widget->set_enable(p_enable);
  m_facture_status_widget->set_enable(p_enable);
  m_facture_reason_widget->set_enable(p_enable);
  m_purchase_configuration_widget->set_enable(p_enable);
  m_city_widget->set_enable(p_enable);
}

//---------------------------------------------------
// Methods inherited from fichier_client_UI_if class
//---------------------------------------------------
// Comunication with user
//------------------------------------------------------------------------------
void main_window::display_warning_message(const std::string & p_title,const std::string & p_text)
{
  QMessageBox::warning(this,p_title.c_str(),p_text.c_str(), QMessageBox::Ok,QMessageBox::Ok);
}

//------------------------------------------------------------------------------
void main_window::display_information_message(const std::string & p_title,const std::string & p_text)
{
  QMessageBox::information (this,p_title.c_str(),p_text.c_str(), QMessageBox::Ok,QMessageBox::Ok);
}

// Interactions with customer search information
//------------------------------------------------------------------------------
void main_window::set_focus_on_customer_search(void)
{
  m_tab_widget->setCurrentWidget(m_search_widget);
}

//------------------------------------------------------------------------------
const std::string main_window::get_search_customer_name(void)const
{
  return m_search_widget->get_customer_name();
}

//------------------------------------------------------------------------------
const std::string main_window::get_search_customer_first_name(void)const
{
  return m_search_widget->get_customer_first_name();
}

//------------------------------------------------------------------------------
const std::string main_window::get_search_customer_address(void)const
{
  return m_search_widget->get_customer_address();
}

//------------------------------------------------------------------------------
const std::string main_window::get_search_customer_city(void)const
{
  return m_search_widget->get_customer_city();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_customer(void)const
{
  return m_search_widget->get_selected_customer();
}

//------------------------------------------------------------------------------
void main_window::update_search_customer_list(const std::vector<search_client_item> & p_list)
{
  m_search_widget->update_customer_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::update_search_customer_list_achat(const std::vector<search_achat_item> & p_list)
{
  m_search_widget->update_customer_list_achat(p_list);
}

//------------------------------------------------------------------------------
void main_window::update_search_customer_list_facture(const std::vector<search_facture_item> & p_list)
{
  m_search_widget->update_customer_list_facture(p_list);
}
//------------------------------------------------------------------------------
void main_window::set_customer_search_add_customer_enabled(bool p_enabled)
{
  m_search_widget->set_add_customer_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_search_modify_customer_enabled(bool p_enabled)
{
  m_search_widget->set_modify_customer_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_search_delete_customer_enabled(bool p_enabled)
{
  m_search_widget->set_delete_customer_enabled(p_enabled);
}


// Interactions with Customer identity information
//------------------------------------------------------------------------------
void main_window::set_focus_on_customer_data(void)
{
  m_tab_widget->setCurrentWidget(m_customer_data_widget);
}

//------------------------------------------------------------------------------
void main_window::set_customer_name(const std::string & p_name)
{
  m_customer_data_widget->set_name(p_name);
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_name(void)const
{
  return m_customer_data_widget->get_name();
}

//------------------------------------------------------------------------------
void main_window::set_customer_first_name(const std::string & p_first_name)
{
  m_customer_data_widget->set_first_name(p_first_name);
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_first_name(void)const
{
  return m_customer_data_widget->get_first_name();
}

//------------------------------------------------------------------------------
void main_window::set_customer_phone(const std::string & p_phone)
{
  m_customer_data_widget->set_phone(p_phone);
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_phone(void)const
{
  return m_customer_data_widget->get_phone();
}

//------------------------------------------------------------------------------
bool main_window::is_customer_phone_empty(void)const
{
  return m_customer_data_widget->is_phone_empty();
}

//------------------------------------------------------------------------------
bool main_window::is_customer_phone_complete(void)const
{
  return m_customer_data_widget->is_phone_complete();
}

//------------------------------------------------------------------------------
void main_window::set_customer_address(const std::string & p_address)
{
  m_customer_data_widget->set_address(p_address);
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_address(void)const
{
  return m_customer_data_widget->get_address();
}

//------------------------------------------------------------------------------
void main_window::set_customer_postal_code(const std::string & p_postal_code)
{
  m_customer_data_widget->set_postal_code(p_postal_code);
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_postal_code(void)const
{
  return m_customer_data_widget->get_postal_code();
}

//------------------------------------------------------------------------------
void main_window::set_customer_city_list(const std::vector<ville> & p_list)
{
  m_customer_data_widget->set_city_list(p_list);
}

//------------------------------------------------------------------------------
const ville * main_window::get_customer_city(void)const
{
  return m_customer_data_widget->get_city();
}

//------------------------------------------------------------------------------
void main_window::set_customer_data_identity_fields_enabled(bool p_enabled)
{
  m_customer_data_widget->set_identity_fields_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_data_create_customer_enabled(bool p_enabled)
{
  m_customer_data_widget->set_create_customer_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_data_modify_customer_enabled(bool p_enabled)
{
  m_customer_data_widget->set_modify_customer_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_data_delete_customer_enabled(bool p_enabled)
{
  m_customer_data_widget->set_delete_customer_enabled(p_enabled);
}

// Interactions with customer bill information
//------------------------------------------------------------------------------
void main_window::set_customer_bill_fields_enabled(bool p_enabled)
{
  m_customer_data_widget->set_bill_fields_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_facture_date(const std::string & p_date)
{
  m_customer_data_widget->set_facture_date(p_date);
}

//------------------------------------------------------------------------------
void main_window::set_customer_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids)
{
  m_customer_data_widget->set_facture_allowed_livre_ids(p_livre_ids);
}

//------------------------------------------------------------------------------
void main_window::set_customer_facture_livre_id(uint32_t p_id)
{
  m_customer_data_widget->set_facture_livre_id(p_id);
}

//------------------------------------------------------------------------------
void main_window::set_customer_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs)
{
  m_customer_data_widget->set_facture_allowed_references(p_remaining_refs);
}

//------------------------------------------------------------------------------
void main_window::set_customer_facture_reference(uint32_t p_ref)
{
  m_customer_data_widget->set_facture_reference(p_ref);
}

//------------------------------------------------------------------------------
void main_window::set_customer_facture_status_list(const std::vector<facture_status> & p_status_list)
{
  m_customer_data_widget->set_facture_status_list(p_status_list);
}

//------------------------------------------------------------------------------
void main_window::set_customer_facture_status(uint32_t p_id)
{
  m_customer_data_widget->set_facture_status(p_id);
}

//------------------------------------------------------------------------------
bool main_window::is_customer_bill_date_complete(void)const
{
  return m_customer_data_widget->is_bill_date_complete();
}

//------------------------------------------------------------------------------
bool main_window::is_customer_bill_date_empty(void)const
{
  return m_customer_data_widget->is_bill_date_empty();
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_bill_date(void)const
{
  return m_customer_data_widget->get_bill_date();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_customer_bill_book_id(void)const
{
  return m_customer_data_widget->get_bill_book_id();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_customer_bill_reference(void)const
{
  return m_customer_data_widget->get_bill_reference();
}

//------------------------------------------------------------------------------
const facture_status * main_window::get_customer_bill_status(void)const
{
  return m_customer_data_widget->get_bill_status();
}


// Interactions with customer bill list
//------------------------------------------------------------------------------
bool main_window::is_customer_data_bill_selection_empty(void)const
{
  return m_customer_data_widget->is_bill_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_customer_data_selected_bill_id(void)const
{
  return m_customer_data_widget->get_selected_bill_id();
}

//------------------------------------------------------------------------------
void main_window::update_customer_data_bill_list(const std::vector<search_facture_item> & p_list)
{
  m_customer_data_widget->update_bill_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::set_customer_bill_list_enabled(bool p_enabled)
{
  m_customer_data_widget->set_bill_list_enabled(p_enabled);  
}

// Interactions with customer bill action
//------------------------------------------------------------------------------
void main_window::set_customer_bill_creation_enabled(bool p_enabled)
{
  m_customer_data_widget->set_bill_creation_enabled(p_enabled);  
}

//------------------------------------------------------------------------------
void main_window::set_customer_bill_modification_enabled(bool p_enabled)
{
  m_customer_data_widget->set_bill_modification_enabled(p_enabled);  
}

//------------------------------------------------------------------------------
void main_window::set_customer_bill_deletion_enabled(bool p_enabled)
{
  m_customer_data_widget->set_bill_deletion_enabled(p_enabled);  
}

// Interactions with customer purchase information
//------------------------------------------------------------------------------
void main_window::set_customer_purchase_fields_enabled(bool p_enabled)
{
  m_customer_data_widget->set_purchase_fields_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_brand_list(const std::vector<marque> & p_list)
{
  m_customer_data_widget->set_purchase_brand_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_brand(uint32_t p_id)
{
  m_customer_data_widget->set_purchase_brand(p_id);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_type_list(const std::vector<type_achat> & p_list)
{
  m_customer_data_widget->set_purchase_type_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_type(uint32_t p_id)
{
  m_customer_data_widget->set_purchase_type(p_id);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_reference(const std::string & p_ref)
{
  m_customer_data_widget->set_purchase_reference(p_ref);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_euro_price(const std::string & p_euro_price)
{
  m_customer_data_widget->set_purchase_euro_price(p_euro_price);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_franc_price(const std::string & p_franc_price)
{
  m_customer_data_widget->set_purchase_franc_price(p_franc_price);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_warranty(bool p_warranty)
{
  m_customer_data_widget->set_purchase_warranty(p_warranty);
}

//------------------------------------------------------------------------------
const marque * main_window::get_customer_purchase_brand(void)const
{
  return m_customer_data_widget->get_purchase_brand();
}

//------------------------------------------------------------------------------
const type_achat * main_window::get_customer_purchase_type(void)const
{
  return m_customer_data_widget->get_purchase_type();
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_purchase_reference(void)const
{
  return m_customer_data_widget->get_purchase_reference();
}
 
//------------------------------------------------------------------------------
const std::string main_window::get_customer_purchase_euro_price(void)const
{
  return m_customer_data_widget->get_purchase_euro_price();
}

//------------------------------------------------------------------------------
const std::string main_window::get_customer_purchase_franc_price(void)const
{
  return m_customer_data_widget->get_purchase_franc_price();
}

//------------------------------------------------------------------------------
bool main_window::is_customer_purchase_warranty_selected(void)const
{
  return m_customer_data_widget->is_purchase_warranty_selected();
}

// Interactions with customer purchase list
//------------------------------------------------------------------------------
bool main_window::is_customer_data_purchase_selection_empty(void)const
{
  return m_customer_data_widget->is_purchase_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_customer_data_selected_purchase_id(void)const
{
  return m_customer_data_widget->get_selected_purchase_id();
}

//------------------------------------------------------------------------------
void main_window::update_customer_data_purchase_list(const std::vector<search_achat_item> & p_list)
{
  m_customer_data_widget->update_purchase_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_list_enabled(bool p_enabled)
{
  m_customer_data_widget->set_purchase_list_enabled(p_enabled);
}

// Interactions with customer purchase actions
//------------------------------------------------------------------------------
void main_window::set_customer_purchase_creation_enabled(bool p_enabled)
{
  m_customer_data_widget->set_purchase_creation_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_modification_enabled(bool p_enabled)
{
  m_customer_data_widget->set_purchase_modification_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_customer_purchase_deletion_enabled(bool p_enabled)
{
  m_customer_data_widget->set_purchase_deletion_enabled(p_enabled);
}


// Interactions with livre facture information
//------------------------------------------------------------------------------
void main_window::clear_livre_facture_information(void)
{
  m_livre_facture_widget->clear_livre_facture_information();
}

//------------------------------------------------------------------------------
void main_window::set_livre_facture_start_date(const std::string & p_date)
{
  m_livre_facture_widget->set_livre_facture_start_date(p_date);
}

//------------------------------------------------------------------------------
void main_window::set_livre_facture_end_date(const std::string & p_date)
{
  m_livre_facture_widget->set_livre_facture_end_date(p_date);
}

//------------------------------------------------------------------------------
void main_window::set_livre_facture_id(const std::string & p_id)
{
  m_livre_facture_widget->set_livre_facture_id(p_id);
}

//------------------------------------------------------------------------------
const std::string main_window::get_livre_facture_start_date(void)const
{
  return m_livre_facture_widget->get_livre_facture_start_date();
}

//------------------------------------------------------------------------------
bool main_window::is_livre_facture_start_date_complete(void)const
{
  return m_livre_facture_widget->is_livre_facture_start_date_complete();
}

//------------------------------------------------------------------------------
const std::string main_window::get_livre_facture_end_date(void)const
{
  return m_livre_facture_widget->get_livre_facture_end_date();
}

//------------------------------------------------------------------------------
bool main_window::is_livre_facture_end_date_complete(void)const
{
  return m_livre_facture_widget->is_livre_facture_end_date_complete();
}

//------------------------------------------------------------------------------
const std::string main_window::get_livre_facture_id(void)const
{
  return m_livre_facture_widget->get_livre_facture_id();
}

// Interactions with livre facture list
//--------------------------------------

//------------------------------------------------------------------------------
bool main_window::is_livre_facture_selection_empty(void)const
{
  return m_livre_facture_widget->is_livre_facture_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_livre_facture_id(void)const
{
  return m_livre_facture_widget->get_selected_livre_facture_id();
}

//------------------------------------------------------------------------------
void main_window::refresh_livre_facture_list(std::vector<livre_facture> & p_list)
{
  m_livre_facture_widget->refresh_livre_facture_list(p_list);
}

// Interactions with livre facture actions
//-----------------------------------------
void main_window::set_delete_livre_facture_enabled(bool p_enabled)
{
  m_livre_facture_widget->set_delete_livre_facture_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_modify_livre_facture_enabled(bool p_enabled)
{
  m_livre_facture_widget->set_modify_livre_facture_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_create_livre_facture_enabled(bool p_enabled)
{
  m_livre_facture_widget->set_create_livre_facture_enabled(p_enabled);
}

// Interactions with non attributed facture information
//-------------------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_date(const std::string & p_date)
{
  m_livre_facture_widget->set_non_attributed_facture_date(p_date);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs)
{
  m_livre_facture_widget->set_allowed_facture_references(p_remaining_refs);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_reference(uint32_t p_ref)
{
   m_livre_facture_widget->set_facture_reference(p_ref);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids)
{
  m_livre_facture_widget->set_allowed_livre_ids(p_livre_ids);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_status_list(const std::vector<facture_status> & p_status_list)
{
  m_livre_facture_widget->set_status_list(p_status_list);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_status(uint32_t p_id)
{
  m_livre_facture_widget->set_status(p_id);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_reason_list(const std::vector<facture_reason> & p_reason_list)
{
  m_livre_facture_widget->set_reason_list(p_reason_list);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_reason(uint32_t p_id)
{
  m_livre_facture_widget->set_reason(p_id);
}

//------------------------------------------------------------------------------
const std::string main_window::get_non_attributed_facture_date(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_date();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_non_attributed_facture_livre_facture_id(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_livre_facture_id();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_non_attributed_facture_reference(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_reference();
}

//------------------------------------------------------------------------------
const facture_status * main_window::get_non_attributed_facture_status(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_status();
}

//------------------------------------------------------------------------------
const facture_reason * main_window::get_non_attributed_facture_reason(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_reason();
}

//------------------------------------------------------------------------------
void main_window::clear_non_attributed_facture_date(void)
{
  m_livre_facture_widget->clear_non_attributed_facture_date();
}

//------------------------------------------------------------------------------
void main_window::enable_non_attributed_facture_fields(bool p_enable)
{
  m_livre_facture_widget->enable_non_attributed_facture_fields(p_enable);
}

//------------------------------------------------------------------------------
bool main_window::is_non_attributed_facture_date_complete(void)const
{
  return m_livre_facture_widget->is_non_attributed_facture_date_complete();
}

//------------------------------------------------------------------------------
bool main_window::is_non_attributed_facture_date_empty(void)const
{
  return m_livre_facture_widget->is_non_attributed_facture_date_empty();
}

// Interactions with non attributed facture list
//-----------------------------------------------
//------------------------------------------------------------------------------
void main_window::refresh_list_facture_of_livre_facture(std::vector<search_facture_client_item> & p_list)
{
  m_livre_facture_widget->refresh_list_facture_of_livre_facture(p_list);
}

//------------------------------------------------------------------------------
bool main_window::is_list_facture_of_livre_facture_selection_empty(void)const
{
  return m_livre_facture_widget->is_list_facture_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_list_facture_of_livre_facture_selected_id(void)const
{
  return m_livre_facture_widget->get_list_facture_selected_id();
}


// Interactions with non attributed facture buttons
//---------------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_facture_creation_for_selected_livre_enabled( bool p_enabled)
{
  m_livre_facture_widget->set_facture_creation_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_facture_deletion_for_selected_livre_enabled( bool p_enabled)
{
  m_livre_facture_widget->set_facture_deletion_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_facture_modification_for_selected_livre_enabled( bool p_enabled)
{
  m_livre_facture_widget->set_facture_modification_enabled(p_enabled);
}

// Interactions with facture status information
//---------------------------------------------
void main_window::clear_facture_status_information(void)
{
  m_facture_status_widget->clear_facture_status_information();
}

//---------------------------------------------
void main_window::set_facture_status_name(const std::string & p_name)
{
  m_facture_status_widget->set_facture_status_name(p_name);
}
 
//---------------------------------------------
const std::string main_window::get_facture_status_name(void)const
{
  return m_facture_status_widget->get_facture_status_name();
}

// Interactions with facture status list
//--------------------------------------
//------------------------------------------------------------------------------
bool main_window::is_facture_status_selection_empty(void)const
{
  return m_facture_status_widget->is_facture_status_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_facture_status_id(void)const
{
  return m_facture_status_widget->get_selected_facture_status_id();
}

//------------------------------------------------------------------------------
void main_window::refresh_facture_status_list(std::vector<facture_status> & p_list)
{
  m_facture_status_widget->refresh_facture_status_list(p_list);
}

//------------------------------------------------------------------------------
void  main_window::set_facture_status_list_enabled(bool p_enable)
{
  m_facture_status_widget->set_facture_status_list_enabled(p_enable);
}

// Interactions with facture status actions
//------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_create_facture_status_enabled(bool p_enable)
{
  m_facture_status_widget->set_create_facture_status_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_delete_facture_status_enabled(bool p_enable)
{
  m_facture_status_widget->set_delete_facture_status_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_status_enabled(bool p_enable)
{
  m_facture_status_widget->set_modify_facture_status_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_status_action_name(const std::string & p_name)
{
  m_facture_status_widget->set_modify_facture_status_action_name(p_name);
}

// Interactions with facture reason information
//---------------------------------------------
void main_window::clear_facture_reason_information(void)
{
  m_facture_reason_widget->clear_facture_reason_information();
}

//---------------------------------------------
void main_window::set_facture_reason_name(const std::string & p_name)
{
  m_facture_reason_widget->set_facture_reason_name(p_name);
}
 
//---------------------------------------------
const std::string main_window::get_facture_reason_name(void)const
{
  return m_facture_reason_widget->get_facture_reason_name();
}

// Interactions with facture reason list
//--------------------------------------
//------------------------------------------------------------------------------
bool main_window::is_facture_reason_selection_empty(void)const
{
  return m_facture_reason_widget->is_facture_reason_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_facture_reason_id(void)const
{
  return m_facture_reason_widget->get_selected_facture_reason_id();
}

//------------------------------------------------------------------------------
void main_window::refresh_facture_reason_list(std::vector<facture_reason> & p_list)
{
  m_facture_reason_widget->refresh_facture_reason_list(p_list);
}

//------------------------------------------------------------------------------
void  main_window::set_facture_reason_list_enabled(bool p_enable)
{
  m_facture_reason_widget->set_facture_reason_list_enabled(p_enable);
}

// Interactions with facture reason actions
//------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_create_facture_reason_enabled(bool p_enable)
{
  m_facture_reason_widget->set_create_facture_reason_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_delete_facture_reason_enabled(bool p_enable)
{
  m_facture_reason_widget->set_delete_facture_reason_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_reason_enabled(bool p_enable)
{
  m_facture_reason_widget->set_modify_facture_reason_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_reason_action_name(const std::string & p_name)
{
  m_facture_reason_widget->set_modify_facture_reason_action_name(p_name);
}

// Interactions with brand information
//------------------------------------------------------------------------------
void main_window::clear_purchase_configuration_brand_information(void)
{
  m_purchase_configuration_widget->clear_brand_information();
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_brand_name(const std::string & p_name)
{
  m_purchase_configuration_widget->set_brand_name(p_name);
}

//------------------------------------------------------------------------------
const std::string main_window::get_purchase_configuration_brand_name(void)const
{
  return m_purchase_configuration_widget->get_brand_name();
}


// Interactions with brand list
//------------------------------------------------------------------------------
bool main_window::is_purchase_configuration_brand_selection_empty(void)const
{
  return m_purchase_configuration_widget->is_brand_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_purchase_configuration_selected_brand_id(void)const
{
  return m_purchase_configuration_widget->get_selected_brand_id();
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_brand_list(std::vector<marque> & p_list)
{
  m_purchase_configuration_widget->set_brand_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_brand_list_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_brand_list_enabled(p_enable);
}


// Interactions with brand actions
//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_create_brand_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_create_brand_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_delete_brand_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_delete_brand_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_modify_brand_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_modify_brand_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_modify_brand_action_name(const std::string & p_name)
{
  m_purchase_configuration_widget->set_modify_brand_action_name(p_name);
}

// Interactions with type information
//------------------------------------------------------------------------------
void main_window::clear_purchase_configuration_type_information(void)
{
  m_purchase_configuration_widget->clear_type_information();
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_type_name(const std::string & p_name)
{
  m_purchase_configuration_widget->set_type_name(p_name);
}

//------------------------------------------------------------------------------
const std::string main_window::get_purchase_configuration_type_name(void)const
{
  return m_purchase_configuration_widget->get_type_name();
}


// Interactions with type list
//------------------------------------------------------------------------------
bool main_window::is_purchase_configuration_type_selection_empty(void)const
{
  return m_purchase_configuration_widget->is_type_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_purchase_configuration_selected_type_id(void)const
{
  return m_purchase_configuration_widget->get_selected_type_id();
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_type_list(std::vector<type_achat> & p_list)
{
  m_purchase_configuration_widget->set_type_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_type_list_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_type_list_enabled(p_enable);
}


// Interactions with type actions
//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_create_type_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_create_type_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_delete_type_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_delete_type_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_modify_type_enabled(bool p_enable)
{
  m_purchase_configuration_widget->set_modify_type_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_purchase_configuration_modify_type_action_name(const std::string & p_name)
{
  m_purchase_configuration_widget->set_modify_type_action_name(p_name);
}

  // Interactions with city information
//------------------------------------------------------------------------------
void main_window::clear_city_information(void)
{
  m_city_widget->clear_city_information();
}

//------------------------------------------------------------------------------
void main_window::set_city_name(const std::string & p_name)
{
  m_city_widget->set_name(p_name);
}

//------------------------------------------------------------------------------
const std::string main_window::get_city_name(void)const
{
  return m_city_widget->get_name();
}

//------------------------------------------------------------------------------
void main_window::set_city_postal_code(const std::string & p_postal_code)
{
  m_city_widget->set_postal_code(p_postal_code);
}
  
//------------------------------------------------------------------------------
const std::string main_window::get_city_postal_code(void)const
{
  return m_city_widget->get_postal_code();
}

//------------------------------------------------------------------------------
bool main_window::is_city_postal_code_complete(void)const
{
  return m_city_widget->is_postal_code_complete();
}

// Interactions with city list
//------------------------------------------------------------------------------
bool main_window::is_city_selection_empty(void)const
{
  return m_city_widget->is_city_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_city_id(void)const
{
  return m_city_widget->get_selected_city_id();
}

//------------------------------------------------------------------------------
void main_window::set_city_list(std::vector<ville> & p_list)
{
  m_city_widget->set_city_list(p_list);
}

//------------------------------------------------------------------------------
void main_window::set_city_list_enabled(bool p_enable)
{
  m_city_widget->set_city_list_enabled(p_enable);
}

// Interactions with city actions
//------------------------------------------------------------------------------
void main_window::set_create_city_enabled(bool p_enable)
{
  m_city_widget->set_create_city_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_delete_city_enabled(bool p_enable)
{
  m_city_widget->set_delete_city_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_city_enabled(bool p_enable)
{
  m_city_widget->set_modify_city_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_city_action_name(const std::string & p_name)
{
  m_city_widget->set_modify_action_name(p_name);
}

//------------------------------------------------------------------------------
void main_window::treat_test_event(void)
{
  test::test();
}

//------------------------------------------------------------------------------
void main_window::treat_import_event(void)
{
  cout << "QtEvent::Import" << endl ;
  QString l_file_name = QFileDialog::getOpenFileName(this,
						     tr("Open Database"), ".",
						     tr("SQL database files (*.sql)"));
  string l_file_name_std = l_file_name.toStdString();
  cout << "File to import is \"" << l_file_name_std << "\"" << endl ;
  if(l_file_name != "")
    {
      m_import_file_action->setEnabled(false);
      m_open_file_action->setEnabled(false);
      m_save_as_action->setEnabled(true);
      m_close_action->setEnabled(true);

      m_fichier_client.import_external_sql(l_file_name_std);
      QMessageBox::information (this,"Import Status","File successfully imported", QMessageBox::Ok,QMessageBox::Ok);

      setWindowTitle(l_file_name);

      manage_features(true);
    }
}


//------------------------------------------------------------------------------
void main_window::treat_open_db_event(void)
{
  cout << "QtEvent::Open" << endl ;
  QString l_file_name = QFileDialog::getOpenFileName(this,
						     tr("Open Database"), ".",
						     tr("Fichier client files (*.sqlite3)"));
  string l_file_name_std = l_file_name.toStdString();
  cout << "File to open is \"" << l_file_name_std << "\"" << endl ;
  if(l_file_name != "")
    {
      m_import_file_action->setEnabled(false);
      m_open_file_action->setEnabled(false);
      m_save_action->setEnabled(true);
      m_save_as_action->setEnabled(true);
      m_close_action->setEnabled(true);

      m_fichier_client.open_db(l_file_name_std);
      QMessageBox::information (this,"Open Status","File successfully opened", QMessageBox::Ok,QMessageBox::Ok);
      setWindowTitle(l_file_name);
      manage_features(true);
    }
}

//------------------------------------------------------------------------------
void main_window::exit(void)
{
  cout << "QtEvent::Exit" << endl ;
  close();
}

//------------------------------------------------------------------------------
void main_window::treat_save_event(void)
{
  cout << "QtEvent::Save" << endl ;
  m_fichier_client.save();
}

//------------------------------------------------------------------------------
void main_window::treat_save_as_event(void)
{
  cout << "QtEvent::Save as" << endl ;
  QString l_file_name = QFileDialog::getSaveFileName(this,
						     tr("Save Database"), ".",
						     tr("Fichier client files (*.sqlite3)"));
  string l_file_name_std = l_file_name.toStdString();
  cout << "File to save is \"" << l_file_name_std << "\"" << endl ;
  if(l_file_name != "")
    {
      m_fichier_client.save_as(l_file_name_std);
      QMessageBox::information (this,"Save Status","File successfully saved", QMessageBox::Ok,QMessageBox::Ok);
      m_save_action->setEnabled(true);
      setWindowTitle(l_file_name);
    }
}

//------------------------------------------------------------------------------
void main_window::treat_close_db_event(void)
{
  cout << "QtEvent::Close" << endl ;
  bool l_close = true;
  if(m_fichier_client.need_save())
    {
      string l_question = "Database has non saved modification\nAre you sure you want to close it ?";
      int l_result = QMessageBox::question(this, tr("Close"),
					   tr(l_question.c_str()),
					   QMessageBox::Yes | QMessageBox::Default,
					   QMessageBox::No);
      if (l_result != QMessageBox::Yes)
	{
	  l_close = false;
	}
    }
  if(l_close)
    {
      m_open_file_action->setEnabled(true);
      m_save_action->setEnabled(false);
      m_save_as_action->setEnabled(false);
      m_close_action->setEnabled(false);
      manage_features(false);
      m_fichier_client.close_db();
      setWindowTitle(tr("Fichier client"));
    }
}

//------------------------------------------------------------------------------
void main_window::closeEvent(QCloseEvent *event)
{
  string l_question("Are you sure want to quit ?");
  if(m_fichier_client.need_save())
    {
      l_question += "\nDatabase has non saved modification\n";
    }
  int l_result = QMessageBox::question(this, tr("Quit"),
				       tr(l_question.c_str()),
				       QMessageBox::Yes | QMessageBox::Default,
				       QMessageBox::No);
  if (l_result == QMessageBox::Yes)
    {
      event->accept();
    }
  else
    {
      event->ignore();
    }
}

//------------------------------------------------------------------------------
void main_window::create_actions(void)
{
  m_import_file_action = new QAction(tr("&Import"),this);
  m_import_file_action->setShortcut(tr("Ctrl+I"));
  m_import_file_action->setStatusTip(tr("Import a file from MySql")); 
  connect(m_import_file_action,SIGNAL(triggered()),this,SLOT(treat_import_event()));

  m_open_file_action = new QAction(tr("&Open"),this);
  m_open_file_action->setShortcut(tr("Ctrl+O"));
  m_open_file_action->setStatusTip(tr("Open a file")); 
  connect(m_open_file_action,SIGNAL(triggered()),this,SLOT(treat_open_db_event()));

  m_save_action = new QAction(tr("&Save"),this);
  m_save_action->setShortcut(tr("Ctrl+S"));
  m_save_action->setStatusTip(tr("Save current file")); 
  connect(m_save_action,SIGNAL(triggered()),this,SLOT(treat_save_event()));

  m_save_as_action = new QAction(tr("&Save As"),this);
  m_save_as_action->setShortcut(tr("Ctrl+E"));
  m_save_as_action->setStatusTip(tr("Save a file with a new name")); 
  connect(m_save_as_action,SIGNAL(triggered()),this,SLOT(treat_save_as_event()));

  m_close_action = new QAction(tr("&Close"),this);
  m_close_action->setShortcut(tr("Ctrl+C"));
  m_close_action->setStatusTip(tr("Close current file")); 
  connect(m_close_action,SIGNAL(triggered()),this,SLOT(treat_close_db_event()));

  m_test_action = new QAction(tr("&Test"),this);
  m_test_action->setShortcut(tr("Ctrl+T"));
  m_test_action->setStatusTip(tr("Launch test actions")); 
  connect(m_test_action,SIGNAL(triggered()),this,SLOT(treat_test_event()));

  m_exit_action = new QAction(tr("&Quit"),this);
  m_exit_action->setShortcut(tr("Ctrl+Q"));
  m_exit_action->setStatusTip(tr("Quit the application")); 
  connect(m_exit_action,SIGNAL(triggered()),this,SLOT(exit()));
}

//------------------------------------------------------------------------------
void main_window::create_menus(void)
{
  m_file_menu = menuBar()->addMenu(tr("&File"));
  //  m_file_menu->addAction(m_import_file_action);
  m_file_menu->addAction(m_open_file_action);
  m_file_menu->addAction(m_save_action);
  m_file_menu->addAction(m_save_as_action);
  //  m_file_menu->addAction(m_test_action);
  m_file_menu->addAction(m_close_action);
  m_file_menu->addAction(m_exit_action);

  // Manage action activation
  m_import_file_action->setEnabled(true);
  m_open_file_action->setEnabled(true);
  m_save_action->setEnabled(false);
  m_save_as_action->setEnabled(false);
  m_test_action->setEnabled(false);
  m_close_action->setEnabled(false);
  m_exit_action->setEnabled(true);
}

//------------------------------------------------------------------------------
void main_window::create_status_bar(void)
{
  m_status_label = new QLabel("Status bar");
  statusBar()->addWidget(m_status_label);
}

//EOF
