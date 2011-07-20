#include "customer_data_widget.h"
#include "fichier_client_QtUi_utils.h"
#include "base_facture_widget.h"
#include "facture_list_table.h"
#include "achat_list_table.h"
#include "fichier_client.h"
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>

customer_data_widget::customer_data_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_name_field(NULL),
  m_first_name_field(NULL),
  m_phone_field(NULL),
  m_address_field(NULL),
  m_postal_code_field(NULL),
  m_city_field(NULL),
  m_create_customer_button(NULL),
  m_modify_customer_button(NULL),
  m_delete_customer_button(NULL),
  m_bill_widget(NULL),
  m_bill_list_table(NULL),
  m_create_bill_button(NULL),
  m_modify_bill_button(NULL),
  m_delete_bill_button(NULL),
  m_brand_field(NULL),
  m_type_field(NULL),
  m_purchase_reference_field(NULL),
  m_euro_price_field(NULL),
  m_franc_price_field(NULL),
  m_warranty_field(NULL),
  m_purchase_list_table(NULL),
  m_create_purchase_button(NULL),
  m_modify_purchase_button(NULL),
  m_delete_purchase_button(NULL),
  m_fichier_client(p_fichier_client)
{

  QVBoxLayout *l_vertical_layout = new QVBoxLayout(this);

  QGroupBox * l_customer_identity = new QGroupBox(tr("Identite Client"));

  QVBoxLayout *l_customer_identity_vertical_layout = new QVBoxLayout();

  QHBoxLayout *l_customer_horizontal_layout1 = new QHBoxLayout();

  QLabel *l_name_label = new QLabel(tr("Nom")+" :");
  l_customer_horizontal_layout1->addWidget(l_name_label);

  m_name_field = new QLineEdit("");
  connect(m_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_identity_content_modification_event()));
  l_customer_horizontal_layout1->addWidget(m_name_field);
  
  l_customer_horizontal_layout1->addStretch();

  QLabel *l_first_name_label = new QLabel(tr("Prenom")+" :");
  l_customer_horizontal_layout1->addWidget(l_first_name_label);

  m_first_name_field = new QLineEdit("");
  connect(m_first_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_identity_content_modification_event()));
  l_customer_horizontal_layout1->addWidget(m_first_name_field);

  l_customer_horizontal_layout1->addStretch();

  QLabel *l_phone_label = new QLabel(tr("Telephone")+" :");
  l_customer_horizontal_layout1->addWidget(l_phone_label);

  m_phone_field = new QLineEdit("");
  m_phone_field->setInputMask("00-00-00-00-00");
  m_phone_field->setFixedSize(110,23);
  connect(m_phone_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_identity_content_modification_event()));
  l_customer_horizontal_layout1->addWidget(m_phone_field);
  
  l_customer_identity_vertical_layout->addLayout(l_customer_horizontal_layout1);

  QHBoxLayout *l_customer_horizontal_layout2 = new QHBoxLayout();

  QLabel *l_address_label = new QLabel(tr("Adresse")+" :");
  l_customer_horizontal_layout2->addWidget(l_address_label);

  m_address_field = new QLineEdit("");
  connect(m_address_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_identity_content_modification_event()));
  l_customer_horizontal_layout2->addWidget(m_address_field);
  
  l_customer_horizontal_layout2->addStretch();

  QLabel *l_postal_code_label = new QLabel(tr("Code postal")+" :");
  l_customer_horizontal_layout2->addWidget(l_postal_code_label);

  m_postal_code_field = new QLineEdit("");
  m_postal_code_field->setInputMask("00000");
  m_postal_code_field->setFixedSize(50,23);
  connect(m_postal_code_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_postal_code_modification_event()));
  l_customer_horizontal_layout2->addWidget(m_postal_code_field);
  
  l_customer_horizontal_layout2->addStretch();

  QLabel *l_city_label = new QLabel(tr("Ville")+" :");
  l_customer_horizontal_layout2->addWidget(l_city_label);

  m_city_field = new QComboBox();
  m_city_field->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  connect(m_city_field,SIGNAL(activated (int)),this, SLOT(treat_city_selection_event()));
  l_customer_horizontal_layout2->addWidget(m_city_field);
  
  l_customer_identity_vertical_layout->addLayout(l_customer_horizontal_layout2);

  QHBoxLayout * l_customer_identity_button_layout = new QHBoxLayout();
  m_create_customer_button = new QPushButton(tr("Creer"));
  connect(m_create_customer_button,SIGNAL(clicked()),this,SLOT(treat_create_customer_event()));
  l_customer_identity_button_layout->addWidget(m_create_customer_button);

  m_modify_customer_button = new QPushButton(tr("Modifier"));
  connect(m_modify_customer_button,SIGNAL(clicked()),this,SLOT(treat_modify_customer_event()));
  l_customer_identity_button_layout->addWidget(m_modify_customer_button);

  m_delete_customer_button = new QPushButton(tr("Supprimer"));
  connect(m_delete_customer_button,SIGNAL(clicked()),this,SLOT(treat_delete_customer_event()));
  l_customer_identity_button_layout->addWidget(m_delete_customer_button);

  l_customer_identity_vertical_layout->addLayout(l_customer_identity_button_layout);

  l_customer_identity->setLayout(l_customer_identity_vertical_layout);

  l_vertical_layout->addWidget(l_customer_identity);

  QGroupBox * l_customer_bills = new QGroupBox(tr("Factures client"));

  QVBoxLayout *l_customer_bills_vertical_layout = new QVBoxLayout();

  m_bill_widget = new base_facture_widget(this);
  connect(m_bill_widget,SIGNAL(new_date_entered()),this, SLOT(treat_date_modification_event()));
  connect(m_bill_widget,SIGNAL(new_facture_ref_selected()),this, SLOT(treat_bill_ref_selected_event()));
  connect(m_bill_widget,SIGNAL(new_livre_facture_selected()),this, SLOT(treat_bill_book_selected_event()));
  connect(m_bill_widget,SIGNAL(new_status_selected()),this, SLOT(treat_status_selected_event()));
  l_customer_bills_vertical_layout->addWidget(m_bill_widget);

  m_bill_list_table = new facture_list_table(this);
  connect(m_bill_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_bill_selected_event()));
  connect(m_bill_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_bill_selection_changed_event()));
  l_customer_bills_vertical_layout->addWidget(m_bill_list_table);

  QHBoxLayout *l_customer_bills_button_layout = new QHBoxLayout();
  m_create_bill_button = new QPushButton(tr("Creer"));
  connect(m_create_bill_button,SIGNAL(clicked()),this,SLOT(treat_create_bill_event()));
  l_customer_bills_button_layout->addWidget(m_create_bill_button);

  m_modify_bill_button = new QPushButton(tr("Modifier"));
  connect(m_modify_bill_button,SIGNAL(clicked()),this,SLOT(treat_modify_bill_event()));
  l_customer_bills_button_layout->addWidget(m_modify_bill_button);

  m_delete_bill_button = new QPushButton(tr("Supprimer"));
  connect(m_delete_bill_button,SIGNAL(clicked()),this,SLOT(treat_delete_bill_event()));
  l_customer_bills_button_layout->addWidget(m_delete_bill_button);

  l_customer_bills_vertical_layout->addLayout(l_customer_bills_button_layout);

  l_customer_bills->setLayout(l_customer_bills_vertical_layout);

  l_vertical_layout->addWidget(l_customer_bills);

  QGroupBox * l_customer_purchases = new QGroupBox(tr("Achats client"));

  QVBoxLayout *l_customer_purchases_vertical_layout = new QVBoxLayout();

  QHBoxLayout *l_customer_purchases_field_layout = new QHBoxLayout();

  QLabel * l_brand_label = new QLabel(tr("Marque")+" :");
  l_customer_purchases_field_layout->addWidget(l_brand_label);

  m_brand_field = new QComboBox();
  m_brand_field->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  connect(m_brand_field, SIGNAL(activated (int)),this,SLOT(treat_brand_selection_event(void)));
  l_customer_purchases_field_layout->addWidget(m_brand_field);

  QLabel * l_type_label = new QLabel(tr("Type")+" :");
  l_customer_purchases_field_layout->addWidget(l_type_label);

  m_type_field = new QComboBox();
  m_type_field->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  connect(m_type_field, SIGNAL(activated (int)),this,SLOT(treat_type_selection_event(void)));
  l_customer_purchases_field_layout->addWidget(m_type_field);

  QLabel * l_reference_label = new QLabel(tr("Reference")+" :");
  l_customer_purchases_field_layout->addWidget(l_reference_label);

  m_purchase_reference_field = new QLineEdit("");
  connect(m_purchase_reference_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_reference_modification_event()));
  l_customer_purchases_field_layout->addWidget(m_purchase_reference_field);

  QLabel * l_euro_price_label = new QLabel(tr("Prix en euros")+" :");
  l_customer_purchases_field_layout->addWidget(l_euro_price_label);

  m_euro_price_field = new QLineEdit("");
  connect(m_euro_price_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_euro_price_modification_event()));
  l_customer_purchases_field_layout->addWidget(m_euro_price_field);

  QLabel * l_franc_price_label = new QLabel(tr("Prix en francs")+" :");
  l_customer_purchases_field_layout->addWidget(l_franc_price_label);

  m_franc_price_field = new QLineEdit("");
  connect(m_franc_price_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_franc_price_modification_event()));
  l_customer_purchases_field_layout->addWidget(m_franc_price_field);

  m_warranty_field = new QCheckBox(tr("Garantie"));
  connect(m_warranty_field,SIGNAL(stateChanged(int)),this, SLOT(treat_warranty_modification_event()));
  l_customer_purchases_field_layout->addWidget(m_warranty_field);

  l_customer_purchases_vertical_layout->addLayout(l_customer_purchases_field_layout);

  m_purchase_list_table = new achat_list_table(this);
  connect(m_purchase_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_purchase_selected_event()));
  connect(m_purchase_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_purchase_selection_changed_event()));
  l_customer_purchases_vertical_layout->addWidget(m_purchase_list_table);

  QHBoxLayout *l_customer_purchases_button_layout = new QHBoxLayout();
  m_create_purchase_button = new QPushButton(tr("Creer"));
  connect(m_create_purchase_button,SIGNAL(clicked()),this,SLOT(treat_create_purchase_event()));
  l_customer_purchases_button_layout->addWidget(m_create_purchase_button);

  m_modify_purchase_button = new QPushButton(tr("Modifier"));
  connect(m_modify_purchase_button,SIGNAL(clicked()),this,SLOT(treat_modify_purchase_event()));
  l_customer_purchases_button_layout->addWidget(m_modify_purchase_button);

  m_delete_purchase_button = new QPushButton(tr("Supprimer"));
  connect(m_delete_purchase_button,SIGNAL(clicked()),this,SLOT(treat_delete_purchase_event()));
  l_customer_purchases_button_layout->addWidget(m_delete_purchase_button);

  l_customer_purchases_vertical_layout->addLayout(l_customer_purchases_button_layout);

  l_customer_purchases->setLayout(l_customer_purchases_vertical_layout);

  l_vertical_layout->addWidget(l_customer_purchases);

}

// Interactions with customer identity information
//------------------------------------------------------------------------------
void customer_data_widget::set_name(const std::string & p_name)
{
  m_name_field->setText(p_name.c_str());
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_name(void)const
{
  return m_name_field->text().toStdString();
}

//------------------------------------------------------------------------------
void customer_data_widget::set_first_name(const std::string & p_first_name)
{
  m_first_name_field->setText(p_first_name.c_str());
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_first_name(void)const
{
  return m_first_name_field->text().toStdString();
}

//------------------------------------------------------------------------------
void customer_data_widget::set_phone(const std::string & p_phone)
{
  assert(p_phone.size()==10 || p_phone.size()==0);
  std::string l_new_phone ;
  if(p_phone.size())
    {
      l_new_phone = p_phone.substr(0,2) + "-" + p_phone.substr(2,2) + "-" + p_phone.substr(4,2) + "-" + p_phone.substr(6,2) + "-" + p_phone.substr(8,2);
    }
  m_phone_field->setText(l_new_phone.c_str());
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_phone(void)const
{
  std::string l_phone = m_phone_field->text().toStdString();
  std::string l_result;
  if(l_phone != "----")
    {
      assert(l_phone.size()==14);
      l_result = l_phone.substr(0,2) + l_phone.substr(3,2) + l_phone.substr(6,2) + l_phone.substr(9,2) + l_phone.substr(12,2);
    }
  
  return l_result;
}

//------------------------------------------------------------------------------
bool customer_data_widget::is_phone_empty(void)const
{
  return m_phone_field->text().toStdString() == "----";
}

//------------------------------------------------------------------------------
bool customer_data_widget::is_phone_complete(void)const
{
  return m_phone_field->text().toStdString().size()==14;
}


//------------------------------------------------------------------------------
void customer_data_widget::set_address(const std::string & p_address)
{
  m_address_field->setText(p_address.c_str());
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_address(void)const
{
  return m_address_field->text().toStdString();
}

//------------------------------------------------------------------------------
void customer_data_widget::set_postal_code(const std::string & p_postal_code)
{
  m_postal_code_field->setText(p_postal_code.c_str());
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_postal_code(void)const
{
  return m_postal_code_field->text().toStdString();
}

//------------------------------------------------------------------------------
void customer_data_widget::set_city_list(const std::vector<ville> & p_list)
{
  fichier_client_QtUi_utils::set_combo_box_named_list<ville>(m_city_field,m_cities,p_list);
}

//------------------------------------------------------------------------------
const ville * customer_data_widget::get_city(void)const
{
  int l_index = m_city_field->currentIndex();
  const ville * l_result = NULL;
  // Check if something is selected
  if(l_index>0 || (!l_index && m_cities.size() == 1))
    {
      uint32_t l_real_index = (m_cities.size() > 1 ? l_index - 1 : 0);
      assert(l_real_index < m_cities.size());
      l_result = &(m_cities[l_real_index]);
    }
  return l_result;
}

//------------------------------------------------------------------------------
void customer_data_widget::set_identity_fields_enabled(bool p_enabled)
{
  m_name_field->setEnabled(p_enabled);
  m_first_name_field->setEnabled(p_enabled);
  m_phone_field->setEnabled(p_enabled);
  m_address_field->setEnabled(p_enabled);
  m_postal_code_field->setEnabled(p_enabled);
  m_city_field->setEnabled(p_enabled);
}

// Interactions with customer identity actions
//------------------------------------------------------------------------------
void customer_data_widget::set_create_customer_enabled(bool p_enabled)
{
  m_create_customer_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_modify_customer_enabled(bool p_enabled)
{
  m_modify_customer_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_delete_customer_enabled(bool p_enabled)
{
  m_delete_customer_button->setEnabled(p_enabled);
}

// Interactions with customer bill information
//------------------------------------------------------------------------------
void customer_data_widget::set_bill_fields_enabled(bool p_enabled)
{
  m_bill_widget->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_facture_date(const std::string & p_date)
{
  m_bill_widget->set_date(p_date);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids)
{
  m_bill_widget->set_allowed_livre_ids(p_livre_ids);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_facture_livre_id(uint32_t p_id)
{
  m_bill_widget->set_livre_id(p_id);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_facture_allowed_references(const std::vector<uint32_t> & p_remaining_refs)
{
  m_bill_widget->set_allowed_facture_ref(p_remaining_refs);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_facture_reference(uint32_t p_ref)
{
  m_bill_widget->set_reference(p_ref);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_facture_status_list(const std::vector<facture_status> & p_status_list)
{
  m_bill_widget->set_status_list(p_status_list);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_facture_status(uint32_t p_id)
{
  m_bill_widget->set_status(p_id); 
}

//------------------------------------------------------------------------------
bool customer_data_widget::is_bill_date_complete(void)const
{
  return m_bill_widget->is_date_complete();
}

//------------------------------------------------------------------------------
bool customer_data_widget::is_bill_date_empty(void)const
{
  return m_bill_widget->is_date_empty();
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_bill_date(void)const
{
  return m_bill_widget->get_iso_date();
}

//------------------------------------------------------------------------------
uint32_t customer_data_widget::get_bill_book_id(void)const
{
  return m_bill_widget->get_livre_facture_id();
}

//------------------------------------------------------------------------------
uint32_t customer_data_widget::get_bill_reference(void)const
{
  return m_bill_widget->get_facture_reference();
}

//------------------------------------------------------------------------------
const facture_status * customer_data_widget::get_bill_status(void)const
{
  return m_bill_widget->get_facture_status();
}

// Interactions with customer bill list
//------------------------------------------------------------------------------
bool customer_data_widget::is_bill_selection_empty(void)const
{
  return m_bill_list_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t customer_data_widget::get_selected_bill_id(void)const
{
  return m_bill_list_table->get_selected_facture_item_id(m_bill_list_table->currentRow());
}

//------------------------------------------------------------------------------
void customer_data_widget::update_bill_list(const std::vector<search_facture_item> & p_list)
{
  m_bill_list_table->update(p_list);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_bill_list_enabled(bool p_enabled)
{
  m_bill_list_table->setEnabled(p_enabled);
}

// Interactions with customer bill action
//------------------------------------------------------------------------------
void customer_data_widget::set_bill_creation_enabled(bool p_enabled)
{
  m_create_bill_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_bill_modification_enabled(bool p_enabled)
{
  m_modify_bill_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_bill_deletion_enabled(bool p_enabled)
{
  m_delete_bill_button->setEnabled(p_enabled);
}

// Interactions with customer purchase information
//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_fields_enabled(bool p_enabled)
{
  m_brand_field->setEnabled(p_enabled);
  m_type_field->setEnabled(p_enabled);
  m_purchase_reference_field->setEnabled(p_enabled);
  m_euro_price_field->setEnabled(p_enabled);
  m_franc_price_field->setEnabled(p_enabled);
  m_warranty_field->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_brand_list(const std::vector<marque> & p_list)
{
  fichier_client_QtUi_utils::set_combo_box_named_list<marque>(m_brand_field,m_brands,p_list);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_brand(uint32_t p_id)
{
  fichier_client_QtUi_utils::select_combo_box_named_content<marque>(p_id,m_brand_field,m_brands);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_type_list(const std::vector<type_achat> & p_list)
{
  fichier_client_QtUi_utils::set_combo_box_named_list<type_achat>(m_type_field,m_purchase_types,p_list);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_type(uint32_t p_id)
{
  fichier_client_QtUi_utils::select_combo_box_named_content<type_achat>(p_id,m_type_field,m_purchase_types);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_reference(const std::string & p_ref)
{
  m_purchase_reference_field->setText(p_ref.c_str());
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_euro_price(const std::string & p_euro_price)
{
  m_euro_price_field->setText(p_euro_price.c_str());
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_franc_price(const std::string & p_franc_price)
{
  m_franc_price_field->setText(p_franc_price.c_str());
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_warranty(bool p_warranty)
{
  m_warranty_field->setChecked(p_warranty);
}

//------------------------------------------------------------------------------
const marque * customer_data_widget::get_purchase_brand(void)const
{
  int l_index = m_brand_field->currentIndex();
  const marque * l_result = NULL;
  // Check if something is selected
  if(l_index > 0 || (!l_index && m_brands.size() == 1))
    {
      uint32_t l_real_index = (m_brands.size() > 1 ? l_index - 1 : 0);
      assert(l_real_index < m_brands.size());
      l_result = &(m_brands[l_real_index]);
    }
  return l_result;
}

//------------------------------------------------------------------------------
const type_achat * customer_data_widget::get_purchase_type(void)const
{
  int l_index = m_type_field->currentIndex();
  const type_achat * l_result = NULL;
  // Check if something is selected
  if(l_index > 0 || (!l_index && m_purchase_types.size() == 1))
    {
      uint32_t l_real_index = (m_purchase_types.size() > 1 ? l_index - 1 : 0);
      assert(l_real_index < m_purchase_types.size());
      l_result = &(m_purchase_types[l_real_index]);
    }
  return l_result;
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_purchase_reference(void)const
{
  return m_purchase_reference_field->text().toStdString();
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_purchase_euro_price(void)const
{
  return m_euro_price_field->text().toStdString();
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_purchase_franc_price(void)const
{
  return m_franc_price_field->text().toStdString();
}

//------------------------------------------------------------------------------
bool customer_data_widget::is_purchase_warranty_selected(void)const
{
  return m_warranty_field->isChecked();
}

// Interactions with customer purchase list
//------------------------------------------------------------------------------
bool customer_data_widget::is_purchase_selection_empty(void)const
{
  return m_purchase_list_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t customer_data_widget::get_selected_purchase_id(void)const
{
  return m_purchase_list_table->get_selected_achat_id(m_purchase_list_table->currentRow());
}

//------------------------------------------------------------------------------
void customer_data_widget::update_purchase_list(const std::vector<search_achat_item> & p_list)
{
  m_purchase_list_table->update(p_list);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_list_enabled(bool p_enabled)
{
  m_purchase_list_table->setEnabled(p_enabled);
}

// Interactions with customer purchase action
//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_creation_enabled(bool p_enabled)
{
  m_create_purchase_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_modification_enabled(bool p_enabled)
{
  m_modify_purchase_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void customer_data_widget::set_purchase_deletion_enabled(bool p_enabled)
{
  m_delete_purchase_button->setEnabled(p_enabled);
}

// Customer identity information event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_postal_code_modification_event(void)
{
  std::cout << "QtEvent::postal code modification event" << std::endl ;
  m_fichier_client.treat_customer_postal_code_modification_event();
  
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_city_selection_event(void)
{
  std::cout << "QtEvent::city selection event" << std::endl ;
  m_fichier_client.treat_customer_city_selection_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_identity_content_modification_event(void)
{
  std::cout << "QtEvent::identity content modification event" << std::endl ;
  m_fichier_client.treat_identity_content_modification_event();
}

// Customer identity actions event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_create_customer_event(void)
{
  std::cout << "QtEvent::customer_data create customer event" << std::endl ;
  m_fichier_client.treat_customer_data_create_customer_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_modify_customer_event(void)
{
  std::cout << "QtEvent::customer_data modify customer event" << std::endl ;
  m_fichier_client.treat_customer_data_modify_customer_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_delete_customer_event(void)
{
  std::cout << "QtEvent::customer_data modify customer event" << std::endl ;
  m_fichier_client.treat_customer_data_delete_customer_event();
}

// Customer bill information event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_date_modification_event(void)
{
  std::cout << "QtEvent::customer_data bill data modification event" << std::endl;
  m_fichier_client.treat_customer_data_bill_date_modification_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_bill_ref_selected_event(void)
{
  std::cout << "QtEvent::customer_data bill ref selection event" << std::endl;
  m_fichier_client.treat_customer_data_bill_ref_selection_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_bill_book_selected_event(void)
{
  std::cout << "QtEvent::customer_data bill book selection event" << std::endl;
  m_fichier_client.treat_customer_data_bill_book_selection_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_status_selected_event(void)
{
  std::cout << "QtEvent::customer_data bill status selection event" << std::endl;
  m_fichier_client.treat_customer_data_bill_status_selection_event();
}

// Customer bill list event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_bill_selected_event(void)
{
  std::cout << "QtEvent::customer_data bill selected event" << std::endl ;
  m_fichier_client.treat_customer_data_bill_selected_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_bill_selection_changed_event(void)
{
  std::cout << "QtEvent::customer_data bill selection changed event" << std::endl ;
  if(m_bill_list_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_customer_data_no_more_bill_selected_event();
    }
}

// Customer bill action event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_create_bill_event(void)
{
  std::cout << "QtEvent::customer_data bill create button clicked event" << std::endl ;
  m_fichier_client.treat_customer_data_bill_creation_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_modify_bill_event(void)
{
  std::cout << "QtEvent::customer_data bill modify button clicked event" << std::endl ;
  m_fichier_client.treat_customer_data_bill_modification_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_delete_bill_event(void)
{
  std::cout << "QtEvent::customer_data bill delete button clicked event" << std::endl ;
  m_fichier_client.treat_customer_data_bill_deletion_event();
}

// Customer purchase information event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_brand_selection_event(void)
{
  std::cout << "QtEvent::customer_data brand selection event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_brand_selection_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_type_selection_event(void)
{
  std::cout << "QtEvent::customer_data type selection event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_type_selection_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_reference_modification_event(void)
{
  std::cout << "QtEvent::customer_data reference modification event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_reference_modification_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_euro_price_modification_event(void)
{
  std::cout << "QtEvent::customer_data euro price modification event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_euro_price_modification_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_franc_price_modification_event(void)
{
  std::cout << "QtEvent::customer_data franc price modification event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_franc_price_modification_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_warranty_modification_event(void)
{
  std::cout << "QtEvent::customer_data warranty modification event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_warranty_modification_event();
}

// Customer purchase list event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_purchase_selected_event(void)
{
  std::cout << "QtEvent::customer_data purchase selected event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_selected_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_purchase_selection_changed_event(void)
{
  std::cout << "QtEvent::customer_data purchase selection changed event" << std::endl ;
  if(m_purchase_list_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_customer_data_no_more_purchase_selected_event();
    }
}
 
// Customer purchase actions event handlers
//------------------------------------------------------------------------------
void customer_data_widget::treat_create_purchase_event(void)
{
  std::cout << "QtEvent::customer_data purchase create button clicked event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_creation_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_modify_purchase_event(void)
{
  std::cout << "QtEvent::customer_data purchase modify button clicked event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_modification_event();
}

//------------------------------------------------------------------------------
void customer_data_widget::treat_delete_purchase_event(void)
{
  std::cout << "QtEvent::customer_data purchase delete button clicked event" << std::endl ;
  m_fichier_client.treat_customer_data_purchase_deletion_event();
}

//EOF
