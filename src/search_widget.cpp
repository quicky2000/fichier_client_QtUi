#include "search_widget.h"
#include "fichier_client.h"
#include "client_list_table.h"
#include "achat_list_table.h"
#include "facture_list_table.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

//------------------------------------------------------------------------------
search_widget::search_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_name_field(NULL),
  m_first_name_field(NULL),
  m_address_field(NULL),
  m_city_field(NULL),
  m_client_list_table(NULL),
  m_add_customer_button(NULL),
  m_modify_customer_button(NULL),
  m_delete_customer_button(NULL),
  m_achat_list_table(NULL),
  m_facture_list_table(NULL),
  m_fichier_client(p_fichier_client)
{
  QWidget * l_frame = this;
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(l_frame);
  QHBoxLayout *layout = new QHBoxLayout();
  l_vertical_layout->addLayout(layout);

  layout->addWidget(new QLabel(tr("Name")+" :"));

  m_name_field = new QLineEdit("");
  layout->addWidget(m_name_field);
  connect(m_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_criteria_modification_event()));

  layout->addWidget(new QLabel(tr("First Name")+" :"));

  m_first_name_field = new QLineEdit("");
  layout->addWidget(m_first_name_field);
  connect(m_first_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_criteria_modification_event()));


  layout->addStretch();
  layout->addWidget(new QLabel(tr("Address")+" :"));

  m_address_field = new QLineEdit("");
  layout->addWidget(m_address_field);
  connect(m_address_field,SIGNAL(textEdited(const QString &)),this, SLOT(treat_criteria_modification_event()));

  layout->addWidget(new QLabel(tr("City")+" :"));

  m_city_field = new QLineEdit("");
  layout->addWidget(m_city_field);
  connect(m_city_field,SIGNAL(textEdited(const QString &)),this, SLOT(treat_criteria_modification_event()));

  l_vertical_layout->addWidget(new QLabel("Client search results :"));

  m_client_list_table = new client_list_table(l_frame);
  l_vertical_layout->addWidget(m_client_list_table);
  connect(m_client_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_customer_selected_event(int)));
  connect(m_client_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_customer_selection_changed_event()));

  QHBoxLayout * l_button_layout = new QHBoxLayout();

  m_add_customer_button = new QPushButton(tr("Ajouter"));
  connect(m_add_customer_button,SIGNAL(clicked()),this,SLOT(treat_add_customer_event()));

  m_modify_customer_button = new QPushButton(tr("Modifier"));
  connect(m_modify_customer_button,SIGNAL(clicked()),this,SLOT(treat_modify_customer_event()));

  m_delete_customer_button = new QPushButton(tr("Supprimer"));
  connect(m_delete_customer_button,SIGNAL(clicked()),this,SLOT(treat_delete_customer_event()));

  l_button_layout->addWidget(m_add_customer_button);
  l_button_layout->addWidget(m_modify_customer_button);
  l_button_layout->addWidget(m_delete_customer_button);

  l_vertical_layout->addLayout(l_button_layout);

  l_vertical_layout->addWidget(new QLabel("Achats for selected client :"));

  m_achat_list_table = new achat_list_table(l_frame);
  l_vertical_layout->addWidget(m_achat_list_table);

  l_vertical_layout->addWidget(new QLabel("Factures for selected client :"));

  m_facture_list_table = new facture_list_table(l_frame);
  l_vertical_layout->addWidget(m_facture_list_table);

}

//------------------------------------------------------------------------------
void search_widget::set_enable(bool p_enable)
{
  m_name_field->setEnabled(p_enable);
  m_first_name_field->setEnabled(p_enable);
  m_city_field->setEnabled(p_enable);
  m_address_field->setEnabled(p_enable);

  m_add_customer_button->setEnabled(false);
  m_modify_customer_button->setEnabled(false);
  m_delete_customer_button->setEnabled(false);

  clear_search_criteria();
}

// Interactions with customer search criteria information
//------------------------------------------------------------------------------
const std::string search_widget::get_customer_name(void)const
{
  return m_name_field->text().toStdString();
}

//------------------------------------------------------------------------------
const std::string search_widget::get_customer_first_name(void)const
{
  return m_first_name_field->text().toStdString();
}

//------------------------------------------------------------------------------
const std::string search_widget::get_customer_address(void)const
{
  return m_address_field->text().toStdString();
}

//------------------------------------------------------------------------------
const std::string search_widget::get_customer_city(void)const
{
  return m_city_field->text().toStdString();
}

//------------------------------------------------------------------------------
void search_widget::clear_search_criteria(void)
{
  m_name_field->setText("");
  m_first_name_field->setText("");
  m_address_field->setText("");
  m_city_field->setText("");   

  m_client_list_table->clear();
  m_achat_list_table->clear();   
  m_facture_list_table->clear();
}

//------------------------------------------------------------------------------
uint32_t search_widget::get_selected_customer(void)const
{
  return m_client_list_table->get_selected_client_id(m_client_list_table->currentRow());
}

//------------------------------------------------------------------------------
void search_widget::update_customer_list(const std::vector<search_client_item> & p_list)
{
  m_client_list_table->update(p_list);
}

//------------------------------------------------------------------------------
void search_widget::update_customer_list_achat(const std::vector<search_achat_item> & p_list)
{
  m_achat_list_table->update(p_list);
}

//------------------------------------------------------------------------------
void search_widget::update_customer_list_facture(const std::vector<search_facture_item> & p_list)
{
  m_facture_list_table->update(p_list);
}

//------------------------------------------------------------------------------
void search_widget::set_add_customer_enabled(bool p_enabled)
{
  m_add_customer_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void search_widget::set_modify_customer_enabled(bool p_enabled)
{
  m_modify_customer_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void search_widget::set_delete_customer_enabled(bool p_enabled)
{
 m_delete_customer_button->setEnabled(p_enabled); 
}

//------------------------------------------------------------------------------
void search_widget::treat_criteria_modification_event(void)
{
  std::cout << "QtEvent::search customer Criteria modification" << std::endl ;
  m_fichier_client.treat_search_customer_criteria_modification_event();
}

//------------------------------------------------------------------------------
void search_widget::treat_customer_selected_event(int p_row)
{
  std::cout << "QtEvent:: search sutomer customer selected at row" << p_row << std::endl ;
  m_fichier_client.treat_search_customer_customer_selected_event();
}

//------------------------------------------------------------------------------
void search_widget::treat_customer_selection_changed_event(void)
{
  std::cout << "QtEvent:: search customer customer selection changed" << std::endl ;
  if(m_client_list_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_search_customer_no_more_customer_selected_event();
    }
}

//------------------------------------------------------------------------------
void search_widget::treat_add_customer_event(void)
{
  std::cout << "QtEvent::Button add customer clicked" << std::endl ;
  m_fichier_client.treat_search_customer_add_customer_event();
}

//------------------------------------------------------------------------------
void search_widget::treat_modify_customer_event(void)
{
  std::cout << "QtEvent::Button modify customer clicked" << std::endl ;
  m_fichier_client.treat_search_customer_modify_customer_event();
}

//------------------------------------------------------------------------------
void search_widget::treat_delete_customer_event(void)
{
  std::cout << "QtEvent::Button delete customer clicked" << std::endl ;
  m_fichier_client.treat_search_customer_delete_customer_event();
}

//EOF
