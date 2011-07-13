#include "customer_data_widget.h"
#include "base_facture_widget.h"
#include "facture_list_table.h"
#include "achat_list_table.h"
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
  m_facture_widget(NULL),
  m_facture_list_table(NULL),
  m_create_facture_button(NULL),
  m_modify_facture_button(NULL),
  m_delete_facture_button(NULL),
  m_brand_field(NULL),
  m_type_field(NULL),
  m_purchase_reference_field(NULL),
  m_euro_price_field(NULL),
  m_franc_price_field(NULL),
  m_warranty_field(NULL),
  m_achat_list_table(NULL),
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
  l_customer_horizontal_layout1->addWidget(m_name_field);
  
  l_customer_horizontal_layout1->addStretch();

  QLabel *l_first_name_label = new QLabel(tr("Prenom")+" :");
  l_customer_horizontal_layout1->addWidget(l_first_name_label);

  m_first_name_field = new QLineEdit("");
  l_customer_horizontal_layout1->addWidget(m_first_name_field);

  l_customer_horizontal_layout1->addStretch();

  QLabel *l_phone_label = new QLabel(tr("Telephone")+" :");
  l_customer_horizontal_layout1->addWidget(l_phone_label);

  m_phone_field = new QLineEdit("");
  m_phone_field->setInputMask("00-00-00-00-00");
  m_phone_field->setFixedSize(100,23);
  l_customer_horizontal_layout1->addWidget(m_phone_field);
  
  l_customer_identity_vertical_layout->addLayout(l_customer_horizontal_layout1);

  QHBoxLayout *l_customer_horizontal_layout2 = new QHBoxLayout();

  QLabel *l_address_label = new QLabel(tr("Adresse")+" :");
  l_customer_horizontal_layout2->addWidget(l_address_label);

  m_address_field = new QLineEdit("");
  l_customer_horizontal_layout2->addWidget(m_address_field);
  
  l_customer_horizontal_layout2->addStretch();

  QLabel *l_postal_code_label = new QLabel(tr("Code postal")+" :");
  l_customer_horizontal_layout2->addWidget(l_postal_code_label);

  m_postal_code_field = new QLineEdit("");
  m_postal_code_field->setInputMask("00000");
  m_postal_code_field->setFixedSize(48,23);
  l_customer_horizontal_layout2->addWidget(m_postal_code_field);
  
  l_customer_horizontal_layout2->addStretch();

  QLabel *l_city_label = new QLabel(tr("Ville")+" :");
  l_customer_horizontal_layout2->addWidget(l_city_label);

  m_city_field = new QLineEdit("");
  l_customer_horizontal_layout2->addWidget(m_city_field);
  
  l_customer_identity_vertical_layout->addLayout(l_customer_horizontal_layout2);

  QHBoxLayout * l_customer_identity_button_layout = new QHBoxLayout();
  m_create_customer_button = new QPushButton(tr("Creer"));
  l_customer_identity_button_layout->addWidget(m_create_customer_button);
  m_modify_customer_button = new QPushButton(tr("Modifier"));
  l_customer_identity_button_layout->addWidget(m_modify_customer_button);
  m_delete_customer_button = new QPushButton(tr("Supprimer"));
  l_customer_identity_button_layout->addWidget(m_delete_customer_button);

  l_customer_identity_vertical_layout->addLayout(l_customer_identity_button_layout);

  l_customer_identity->setLayout(l_customer_identity_vertical_layout);

  l_vertical_layout->addWidget(l_customer_identity);

  QGroupBox * l_customer_bills = new QGroupBox(tr("Factures client"));

  QVBoxLayout *l_customer_bills_vertical_layout = new QVBoxLayout();

  m_facture_widget = new base_facture_widget(this);
  l_customer_bills_vertical_layout->addWidget(m_facture_widget);

  m_facture_list_table = new facture_list_table(this);
  l_customer_bills_vertical_layout->addWidget(m_facture_list_table);

  QHBoxLayout *l_customer_bills_button_layout = new QHBoxLayout();
  m_create_facture_button = new QPushButton(tr("Creer"));
  l_customer_bills_button_layout->addWidget(m_create_facture_button);
  m_modify_facture_button = new QPushButton(tr("Modifier"));
  l_customer_bills_button_layout->addWidget(m_modify_facture_button);
  m_delete_facture_button = new QPushButton(tr("Supprimer"));
  l_customer_bills_button_layout->addWidget(m_delete_facture_button);

  l_customer_bills_vertical_layout->addLayout(l_customer_bills_button_layout);

  l_customer_bills->setLayout(l_customer_bills_vertical_layout);

  l_vertical_layout->addWidget(l_customer_bills);

  QGroupBox * l_customer_purchases = new QGroupBox(tr("Achats client"));

  QVBoxLayout *l_customer_purchases_vertical_layout = new QVBoxLayout();

  QHBoxLayout *l_customer_purchases_field_layout = new QHBoxLayout();

  QLabel * l_brand_label = new QLabel(tr("Marque")+" :");
  l_customer_purchases_field_layout->addWidget(l_brand_label);

  m_brand_field = new QComboBox();
  l_customer_purchases_field_layout->addWidget(m_brand_field);

  QLabel * l_type_label = new QLabel(tr("Type")+" :");
  l_customer_purchases_field_layout->addWidget(l_type_label);

  m_type_field = new QComboBox();
  l_customer_purchases_field_layout->addWidget(m_type_field);

  QLabel * l_reference_label = new QLabel(tr("Reference")+" :");
  l_customer_purchases_field_layout->addWidget(l_reference_label);

  m_purchase_reference_field = new QLineEdit("");
  l_customer_purchases_field_layout->addWidget(m_purchase_reference_field);

  QLabel * l_euro_price_label = new QLabel(tr("Prix en euros")+" :");
  l_customer_purchases_field_layout->addWidget(l_euro_price_label);

  m_euro_price_field = new QLineEdit("");
  l_customer_purchases_field_layout->addWidget(m_euro_price_field);

  QLabel * l_franc_price_label = new QLabel(tr("Prix en francs")+" :");
  l_customer_purchases_field_layout->addWidget(l_franc_price_label);

  m_franc_price_field = new QLineEdit("");
  l_customer_purchases_field_layout->addWidget(m_franc_price_field);

  m_warranty_field = new QCheckBox(tr("Garantie"));
  l_customer_purchases_field_layout->addWidget(m_warranty_field);

  l_customer_purchases_vertical_layout->addLayout(l_customer_purchases_field_layout);

  m_achat_list_table = new achat_list_table(this);
  l_customer_purchases_vertical_layout->addWidget(m_achat_list_table);

  QHBoxLayout *l_customer_purchases_button_layout = new QHBoxLayout();
  m_create_purchase_button = new QPushButton(tr("Creer"));
  l_customer_purchases_button_layout->addWidget(m_create_purchase_button);
  m_modify_purchase_button = new QPushButton(tr("Modifier"));
  l_customer_purchases_button_layout->addWidget(m_modify_purchase_button);
  m_delete_purchase_button = new QPushButton(tr("Supprimer"));
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
  m_phone_field->setText(p_phone.c_str());
}

//------------------------------------------------------------------------------
const std::string customer_data_widget::get_phone(void)const
{
  return m_phone_field->text().toStdString();
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


//EOF
