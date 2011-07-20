#include "city_widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "postal_code_widget.h"
#include "city_list_table.h"
#include "fichier_client.h"

//------------------------------------------------------------------------------
city_widget::city_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_postal_code_field(NULL),
  m_name_field(NULL),
  m_city_list_table(NULL),
  m_create_button(NULL),
  m_modify_button(NULL),
  m_delete_button(NULL),
  m_fichier_client(p_fichier_client)
{
  QVBoxLayout * l_main_layout = new QVBoxLayout(this);

  QHBoxLayout * l_field_layout = new QHBoxLayout();

  QLabel * l_postal_code_label = new QLabel(tr("Code postal"));
  l_field_layout->addWidget(l_postal_code_label);

  m_postal_code_field = new postal_code_widget();
  connect(m_postal_code_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_criteria_modification_event()));
  l_field_layout->addWidget(m_postal_code_field);

  QLabel * l_city_label = new QLabel(tr("Ville"));
  l_field_layout->addWidget(l_city_label);

  m_name_field = new QLineEdit("");
  connect(m_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_criteria_modification_event()));
  l_field_layout->addWidget(m_name_field);

  l_main_layout->addLayout(l_field_layout);

  m_city_list_table = new city_list_table(this);
  connect(m_city_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_city_selected_event()));
  connect(m_city_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_city_selection_changed_event()));
  l_main_layout->addWidget(m_city_list_table);

  QHBoxLayout * l_button_layout = new QHBoxLayout();
  m_create_button = new QPushButton(tr("Creer"));
  connect(m_create_button,SIGNAL(clicked()),this,SLOT(treat_create_event()));
  l_button_layout->addWidget(m_create_button);
  
  m_modify_button = new QPushButton(tr("Modifier"));
  connect(m_modify_button,SIGNAL(clicked()),this,SLOT(treat_modify_event()));
  l_button_layout->addWidget(m_modify_button);
  
  m_delete_button = new QPushButton(tr("Supprimer"));
  connect(m_delete_button,SIGNAL(clicked()),this,SLOT(treat_delete_event()));
  l_button_layout->addWidget(m_delete_button);

  l_main_layout->addLayout(l_button_layout);

}

//------------------------------------------------------------------------------
void city_widget::set_enable(bool p_enabled)
{
  m_postal_code_field->setEnabled(p_enabled);
  m_name_field->setEnabled(p_enabled);

  m_city_list_table->setEnabled(p_enabled);

  m_create_button->setEnabled(false);
  m_modify_button->setEnabled(false);
  m_delete_button->setEnabled(false);
}

// Interactions with city information
//------------------------------------------------------------------------------
void city_widget::clear_city_information(void)
{
  m_postal_code_field->setText("");
  m_name_field->setText("");
}

//------------------------------------------------------------------------------
void city_widget::set_name(const std::string & p_name)
{
  m_name_field->setText(p_name.c_str());
}

//------------------------------------------------------------------------------
const std::string city_widget::get_name(void)const
{
  return m_name_field->text().toStdString();
}

//------------------------------------------------------------------------------
void city_widget::set_postal_code(const std::string & p_postal_code)
{
  m_postal_code_field->setText(p_postal_code.c_str());
}

//------------------------------------------------------------------------------
const std::string city_widget::get_postal_code(void)const
{
  return m_postal_code_field->text().toStdString();
}

//------------------------------------------------------------------------------
bool city_widget::is_postal_code_complete(void)const
{
  return m_postal_code_field->is_complete();
}

// Interactions with city list
//------------------------------------------------------------------------------
bool city_widget::is_city_selection_empty(void)const
{
  return m_city_list_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t city_widget::get_selected_city_id(void)const
{
  return m_city_list_table->get_selected_city_id(m_city_list_table->currentRow());
}

//------------------------------------------------------------------------------
void city_widget::set_city_list(std::vector<ville> & p_list)
{
  m_city_list_table->update(p_list);
}

//------------------------------------------------------------------------------
void city_widget::set_city_list_enabled(bool p_enable)
{
  m_city_list_table->setEnabled(p_enable);
}

// Interactions with city actions
//------------------------------------------------------------------------------
void city_widget::set_create_city_enabled(bool p_enable)
{
  m_create_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void city_widget::set_delete_city_enabled(bool p_enable)
{
  m_delete_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void city_widget::set_modify_city_enabled(bool p_enable)
{
  m_modify_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void city_widget::set_modify_action_name(const std::string & p_name)
{
  m_modify_button->setText(p_name.c_str());
}


// City information related events handler
//------------------------------------------------------------------------------
void city_widget::treat_criteria_modification_event(void)
{
  std::cout << "QtEvent::city_widget criteria modification event" << std::endl;
  m_fichier_client.treat_city_criteria_modification_event();
}

  // City list related events handler
//------------------------------------------------------------------------------
void city_widget::treat_city_selected_event(void)
{
  std::cout << "QtEvent::city_widget city selection event" << std::endl;
  m_fichier_client.treat_city_selection_event();
}

//------------------------------------------------------------------------------
void city_widget::treat_city_selection_changed_event(void)
{
  std::cout << "QtEvent::city_widget city selection changed event" << std::endl;
  m_fichier_client.treat_city_no_more_selected_event();
}

// City action related events handler
//------------------------------------------------------------------------------
void city_widget::treat_create_event(void)
{
  std::cout << "QtEvent::city_widget city create button clicked event" << std::endl;
  m_fichier_client.treat_city_create_event();
}

//------------------------------------------------------------------------------
void city_widget::treat_modify_event(void)
{
  std::cout << "QtEvent::city_widget city modify button clicked event" << std::endl;
  m_fichier_client.treat_city_modify_event();
}

//------------------------------------------------------------------------------
void city_widget::treat_delete_event(void)
{
  std::cout << "QtEvent::city_widget city delete button clicked event" << std::endl;
  m_fichier_client.treat_city_delete_event();
}

//EOF
