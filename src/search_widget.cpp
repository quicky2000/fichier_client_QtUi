#include "search_widget.h"
#include "fichier_client.h"
#include "client_list_table.h"
#include "achat_list_table.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
search_widget::search_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_name_field(NULL),
  m_first_name_field(NULL),
  m_city_field(NULL),
  m_client_list_table(NULL),
  m_achat_list_table(NULL),
  m_fichier_client(p_fichier_client)
{
  // QFrame * l_frame = new QFrame();
  QWidget * l_frame = this;
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(l_frame);
  QHBoxLayout *layout = new QHBoxLayout(l_frame);
  l_vertical_layout->addLayout(layout);

  layout->addWidget(new QLabel(tr("Name")+" :"));

  m_name_field = new QLineEdit("");
  layout->addWidget(m_name_field);
  connect(m_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(criteria_modification()));

  layout->addWidget(new QLabel(tr("First Name")+" :"));

  m_first_name_field = new QLineEdit("");
  layout->addWidget(m_first_name_field);
  connect(m_first_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(criteria_modification()));


  layout->addStretch();
  layout->addWidget(new QLabel(tr("City")+" :"));

  m_city_field = new QLineEdit("");
  layout->addWidget(m_city_field);
  connect(m_city_field,SIGNAL(textEdited(const QString &)),this, SLOT(criteria_modification()));

  l_vertical_layout->addWidget(new QLabel("Client search results :"));

  m_client_list_table = new client_list_table(l_frame);
  l_vertical_layout->addWidget(m_client_list_table);
  connect(m_client_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(client_selected(int)));

  l_vertical_layout->addWidget(new QLabel("Achats for selected client :"));

  m_achat_list_table = new achat_list_table(l_frame);
  l_vertical_layout->addWidget(m_achat_list_table);

  //  setCentralWidget(l_frame);

}

//------------------------------------------------------------------------------
void search_widget::set_enable(bool p_enable)
{
  m_name_field->setEnabled(p_enable);
  m_first_name_field->setEnabled(p_enable);
  m_city_field->setEnabled(p_enable);

  m_name_field->setText("");
  m_first_name_field->setText("");
  m_city_field->setText("");   

  m_client_list_table->clearContents();
  m_achat_list_table->clearContents();      
}


//------------------------------------------------------------------------------
void search_widget::criteria_modification(void)
{
  cout << "Criteria modification" << endl ;
  string l_name = m_name_field->text().toStdString();
  string l_first_name = m_first_name_field->text().toStdString();
  string l_city = m_city_field->text().toStdString();
  cout << "Name = \"" << l_name << "\"\tFirst name = \"" << l_first_name << "\"\tCity = \"" << l_city << "\"" << endl ;
  vector<search_client_item> l_result ;
  m_fichier_client.search_client(l_name,l_first_name,l_city,l_result);
  m_client_list_table->update(l_result);
}

//------------------------------------------------------------------------------
void search_widget::client_selected(int p_row)
{
  cout << "Row selected " << p_row << endl ;
  uint32_t l_client_id = m_client_list_table->get_selected_client_id(p_row);
  cout << "Id of selected client " << l_client_id << endl;
  vector<search_achat_item> l_list_achat;
  m_fichier_client.get_achat_by_client_id(l_client_id,l_list_achat);
  m_achat_list_table->update(l_list_achat);  
}

//EOF
