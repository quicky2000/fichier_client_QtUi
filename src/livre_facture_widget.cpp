#include "livre_facture_widget.h"
#include "livre_facture_table.h"
#include "fichier_client.h"

#include "my_date_widget.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
livre_facture_widget::livre_facture_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_create_livre_facture_button(NULL),
  m_delete_livre_facture_button(NULL),
  m_modify_livre_facture_button(NULL),
  m_livre_id_field(NULL),
  m_start_date_field(NULL),
  m_end_date_field(NULL),
  m_livre_facture_table(NULL),
  //  m_achat_list_table(NULL),
  m_fichier_client(p_fichier_client)
{
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(this);
  QHBoxLayout *l_horizontal_layout = new QHBoxLayout(this);
  l_vertical_layout->addLayout(l_horizontal_layout);

  l_horizontal_layout->addWidget(new QLabel(tr("Id")+" :"));

  m_livre_id_field = new QLineEdit("");
  m_livre_id_field->setInputMask("999999");

  l_horizontal_layout->addWidget(m_livre_id_field);
  connect(m_livre_id_field,SIGNAL(textEdited(const QString&)),this, SLOT(criteria_modification()));

  l_horizontal_layout->addStretch();
  l_horizontal_layout->addWidget(new QLabel(tr("Start Date")+" :"));

  //  m_start_date_field = new QLineEdit("");
  m_start_date_field = new my_date_widget();
  l_horizontal_layout->addWidget(m_start_date_field);
  connect(m_start_date_field,SIGNAL(textEdited(const QString&)),this, SLOT(content_modification()));


  l_horizontal_layout->addStretch();
  l_horizontal_layout->addWidget(new QLabel(tr("End Date")+" :"));

  //  m_end_date_field = new QLineEdit("");
  m_end_date_field = new my_date_widget();
  l_horizontal_layout->addWidget(m_end_date_field);
  connect(m_end_date_field,SIGNAL(textEdited(const QString &)),this, SLOT(content_modification()));

  l_vertical_layout->addWidget(new QLabel(tr("Livres de facture")+" :"));

  m_livre_facture_table = new livre_facture_table(this);
  l_vertical_layout->addWidget(m_livre_facture_table);
  connect(m_livre_facture_table,SIGNAL(cellClicked (int, int)),this, SLOT(livre_facture_selected(int)));
  connect(m_livre_facture_table,SIGNAL(itemSelectionChanged()),this, SLOT(livre_facture_selection_changed()));



  m_create_livre_facture_button = new QPushButton(tr("&Create"),this);
  m_create_livre_facture_button->setEnabled(false);
  connect(m_create_livre_facture_button,SIGNAL(clicked()),this,SLOT(create_livre_facture()));

  m_delete_livre_facture_button = new QPushButton(tr("&Delete"),this);
  m_delete_livre_facture_button->setEnabled(false);
  connect(m_delete_livre_facture_button,SIGNAL(clicked()),this,SLOT(delete_livre_facture()));

  m_modify_livre_facture_button = new QPushButton(tr("&Modify"),this);
  m_modify_livre_facture_button->setEnabled(false);
  connect(m_modify_livre_facture_button,SIGNAL(clicked()),this,SLOT(modify_livre_facture()));

  QHBoxLayout *l_button_layout = new QHBoxLayout(this);
  l_vertical_layout->addLayout(l_button_layout);

  l_button_layout->addWidget(m_create_livre_facture_button);
  l_button_layout->addWidget(m_delete_livre_facture_button);
  l_button_layout->addWidget(m_modify_livre_facture_button);

  //connect(m_client_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(client_selected(int)));

  //  l_vertical_layout->addWidget(new QLabel("Achats for selected client :"));

  //  m_achat_list_table = new achat_list_table(l_frame);
  //  l_vertical_layout->addWidget(m_achat_list_table);

}

//------------------------------------------------------------------------------
void livre_facture_widget::livre_facture_selection_changed(void)
{
  cout << "livre_facture_selection_changed" << endl ;
  if(m_livre_facture_table->selectedItems().isEmpty())
    {
      m_delete_livre_facture_button->setEnabled(false);
      m_modify_livre_facture_button->setEnabled(false);
    }
}


//------------------------------------------------------------------------------
uint32_t livre_facture_widget::get_selected_livre_facture_id(void)
{
  return m_livre_facture_table->get_selected_livre_facture_id(m_livre_facture_table->currentRow());
}

//------------------------------------------------------------------------------
void livre_facture_widget::get_selected_livre_facture(livre_facture & p_selected)
{
  uint32_t l_status = m_fichier_client.get_livre_facture(get_selected_livre_facture_id(),p_selected);
  assert(l_status);
}

//------------------------------------------------------------------------------
void livre_facture_widget::delete_livre_facture(void)
{
  livre_facture l_selected;
  get_selected_livre_facture(l_selected);
  m_fichier_client.remove(l_selected);
  m_delete_livre_facture_button->setEnabled(false);
  m_modify_livre_facture_button->setEnabled(false);
  clear_text_fields();
  criteria_modification();
}

//------------------------------------------------------------------------------
void livre_facture_widget::modify_livre_facture(void)
{
  livre_facture l_selected;
  get_selected_livre_facture(l_selected);
  string l_start_date = m_start_date_field->get_iso_date();
  string l_end_date = m_end_date_field->get_iso_date();
  if(l_start_date < l_end_date)
    {
      l_selected.setStartDate(l_start_date);
      l_selected.setEndDate(l_end_date);
      m_fichier_client.update(l_selected);
      criteria_modification();
      m_start_date_field->setText("");
      m_end_date_field->setText("");
    }
  else
    {
      QMessageBox::warning(this,"Livre facture creation error","Start date > End date", QMessageBox::Ok,QMessageBox::Ok);
    }

}


//------------------------------------------------------------------------------
void livre_facture_widget::create_livre_facture(void)
{
  cout << "Create livre facture" << endl ;
  if(m_start_date_field->is_complete() && m_end_date_field->is_complete() )
    {
      string l_start_date = m_start_date_field->get_iso_date();
      string l_end_date = m_end_date_field->get_iso_date();
      if(l_start_date < l_end_date)
	{
	  m_create_livre_facture_button->setEnabled(false);
	  livre_facture l_livre(strtol(m_livre_id_field->text().toStdString().c_str(),NULL,10),
				l_start_date,
				l_end_date);
	  
	  m_fichier_client.create(l_livre);
	  clear_text_fields();
	  criteria_modification();
	}
      else
	{
	  QMessageBox::warning(this,"Livre facture creation error","Start date > End date", QMessageBox::Ok,QMessageBox::Ok);
	}
    }
  else
    {
      QMessageBox::warning(this,"Livre facture creation error","Cannot create livre_facture due to incomplrte date", QMessageBox::Ok,QMessageBox::Ok);
   }
}

//------------------------------------------------------------------------------
void livre_facture_widget::clear_text_fields(void)
{
  m_livre_id_field->setText("");
  m_start_date_field->setText("");
  m_end_date_field->setText("");   
}


//------------------------------------------------------------------------------
void livre_facture_widget::set_enable(bool p_enable)
{
  m_livre_id_field->setEnabled(p_enable);
  m_start_date_field->setEnabled(p_enable);
  m_end_date_field->setEnabled(p_enable);

  clear_text_fields();

  m_delete_livre_facture_button->setEnabled(false);
  m_modify_livre_facture_button->setEnabled(false);

  m_livre_facture_table->clearContents();
  //  m_achat_list_table->clearContents();   
  if(p_enable)
    {
      criteria_modification();
    }
}


//------------------------------------------------------------------------------
void livre_facture_widget::content_modification(void)
{
  cout << "Content modification" << endl ;
  if(!m_livre_facture_table->selectedItems().isEmpty())
    {
      if(m_start_date_field->is_complete() && m_end_date_field->is_complete())
	{
	  string l_start_date = m_start_date_field->get_iso_date();
	  string l_end_date = m_end_date_field->get_iso_date();
	  livre_facture l_selected;
	  get_selected_livre_facture(l_selected);
	  if(l_selected.getStartDate() != l_start_date || l_selected.getEndDate() != l_end_date)
	    {
	      m_modify_livre_facture_button->setEnabled(true);
	    }
	  else
	    {
	      m_modify_livre_facture_button->setEnabled(false);
	    }
	}
    }
}

//------------------------------------------------------------------------------
void livre_facture_widget::criteria_modification(void)
{
  cout << "Criteria modification" << endl ;
  m_create_livre_facture_button->setEnabled(false);
  string l_livre_id = m_livre_id_field->text().toStdString();
  cout << "Id = \"" << l_livre_id << "\"" << endl ;
  vector<livre_facture> l_vector;
  if(l_livre_id.length() == 6)
    {
      livre_facture l_result ;
      uint32_t l_status = m_fichier_client.get_livre_facture(strtol(l_livre_id.c_str(),NULL,10),l_result);
      if(l_status == 1)
	{
	l_vector.push_back(l_result); 
	}
      else
	{
	  QMessageBox::warning(this,"Livre facture search",("No livre facture with id "+l_livre_id+"\n, You can create it by clicking on \"Create\" button").c_str(), QMessageBox::Ok,QMessageBox::Ok);
	  m_create_livre_facture_button->setEnabled(true);
	}
    }
  else
    {
      m_fichier_client.get_all_livre_facture(l_vector);
    }
  m_livre_facture_table->update(l_vector);
}

//------------------------------------------------------------------------------
void livre_facture_widget::livre_facture_selected(int p_row)
{
    cout << "Row selected " << p_row << endl ;
    cout << "Id of selected livre_facture " << get_selected_livre_facture_id() << endl;
    m_delete_livre_facture_button->setEnabled(true);
    livre_facture l_selected;
    get_selected_livre_facture(l_selected);
    stringstream l_id_stream;
    l_id_stream << l_selected.get_id();
    m_livre_id_field->setText(l_id_stream.str().c_str());
    m_start_date_field->set_iso_date(l_selected.getStartDate().c_str());
    m_end_date_field->set_iso_date(l_selected.getEndDate().c_str());
    
  //  vector<search_achat_item> l_list_achat;
  //  m_fichier_client.get_achat_by_client_id(l_client_id,l_list_achat);
  //  m_achat_list_table->update(l_list_achat);  
}

//EOF
